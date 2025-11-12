#include "pch.h"
#include "Field.h"


using namespace RendUI;

// helper для std::visit с несколькими лямбдами
template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

Field::Field(const sf::Vector2f& pos, const sf::Vector2f& sz)
    : background(sz, 12.f),
    position(pos),
    size(sz),
    elementSpacing(4.f),
    scrollOffset(0.f),
    totalContentHeight(0.f),
    scrollbarWidth(10.f),
    draggingScrollbar(false),
    dragStartY(0.f),
    initialScrollOffset(0.f)
{
    background.setPosition(position);
    background.setFillColor(bgColor);
    background.setOutlineThickness(1.5f);
    background.setOutlineColor(borderColor);

    scrollbar.setFillColor(sf::Color(180, 180, 180, 200));
    scrollbar.setSize({ scrollbarWidth, size.y });
}

void Field::update() {
    // Удаляем элементы, которые помечены для удаления
    elements.erase(
        std::remove_if(elements.begin(), elements.end(),
            [](const std::unique_ptr<FieldElement>& el) {
                auto item = dynamic_cast<ItemElement*>(el.get());
                return item && item->markedForDeletion;
            }),
        elements.end()
    );
}

void Field::addRawElement(std::unique_ptr<FieldElement>&& el) {
    if (!el) return;
    totalContentHeight += el->getHeight() + elementSpacing;
    elements.push_back(std::move(el));
}

void Field::clear() {
    elements.clear();
    totalContentHeight = 0.f;
    scrollOffset = 0.f;
}

void Field::draw(sf::RenderWindow& window, const sf::View& view) {
    Field::update();

    // yCenter — верхняя координата поля (по желанию ты центрируешь фон по view)
    float yCenter = view.getCenter().y - size.y / 2.f;
    background.setPosition({ position.x, yCenter });
    window.draw(background);

    // отрисовываем элементы, только те, что попадают в видимую область поля
    float y = yCenter + 5.f - scrollOffset;
    const float contentWidth = size.x - scrollbarWidth - 6.f; // отступы учтены в draw

    for (auto& el : elements) {
        float h = el->getHeight();
        if (y + h < yCenter || y > yCenter + size.y) {
            // за пределами видимости, просто смещаемся и не рисуем
            y += h + elementSpacing;
            continue;
        }

        // передаём позицию верхнего левого угла элемента
        el->draw(window, { position.x + 5.f, y }, contentWidth);
        y += h + elementSpacing;
    }

    // скроллбар (рисуется поверх)
    if (totalContentHeight > size.y) {
        float scrollRatio = size.y / totalContentHeight;
        float scrollbarHeight = size.y * scrollRatio;
        float scrollbarY = yCenter + (scrollOffset / (totalContentHeight - size.y)) * (size.y - scrollbarHeight);
        scrollbar.setPosition({ position.x + size.x - scrollbarWidth, scrollbarY });
        scrollbar.setSize({ scrollbarWidth, scrollbarHeight });
        window.draw(scrollbar);
    }
}

void Field::handleEvent(const sf::Event& event, sf::RenderWindow& window, const sf::View& view) {

    // mouse pos in same coords as view (то, в которых мы рисуем фон/элементы)
    sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel, view);
    float yCenter = view.getCenter().y - size.y / 2.f;

    // ---- drag scrollbar ----
    if (event.is<sf::Event::MouseButtonPressed>()) {
        const auto* mb = event.getIf<sf::Event::MouseButtonPressed>();
        if (mb && mb->button == sf::Mouse::Button::Left) {
            if (scrollbar.getGlobalBounds().contains(mousePos) && totalContentHeight > size.y) {
                draggingScrollbar = true;
                dragStartY = mousePos.y;
                initialScrollOffset = scrollOffset;
            }
        }
    }

    if (event.is<sf::Event::MouseButtonReleased>()) {
        const auto* mb = event.getIf<sf::Event::MouseButtonReleased>();
        if (mb && mb->button == sf::Mouse::Button::Left) {
            draggingScrollbar = false;
        }
    }

    if (event.is<sf::Event::MouseMoved>() && draggingScrollbar && totalContentHeight > size.y) {
        // движение ползунка меняет scrollOffset
        sf::Vector2i mpix = sf::Mouse::getPosition(window);
        sf::Vector2f mpos = window.mapPixelToCoords(mpix, view);
        float deltaY = mpos.y - dragStartY;

        float scrollbarHeight = scrollbar.getSize().y;
        float scrollArea = size.y - scrollbarHeight;
        if (scrollArea <= 0) return;

        float scrollRatio = (totalContentHeight - size.y) / scrollArea;
        scrollOffset = initialScrollOffset + deltaY * scrollRatio;
        if (scrollOffset < 0.f) scrollOffset = 0.f;
        if (scrollOffset > totalContentHeight - size.y) scrollOffset = totalContentHeight - size.y;
    }
    // ---- end drag scrollbar ----

    // ---- forward events to elements (they get their own local position) ----
    float y = yCenter + 5.f - scrollOffset;
    for (auto& el : elements) {
        // позиция верхнего левого угла элемента
        sf::Vector2f elemPos = { position.x + 5.f, y };
        // Передаём mousePos (уже в координатах view!) — элемент сравнит mousePos с elemRect
        el->handleEvent(event, elemPos, size.x - scrollbarWidth, mousePos);
        // если элемент был кликнут
        auto* item = dynamic_cast<RendUI::ItemElement*>(el.get());
        if (item && item->selected) {
            setSelectedElement(item); // <-- снимаем выделение с остальных
        }
        y += el->getHeight() + 4.f;
    }
}

bool Field::isMouseOver(const sf::RenderWindow& window, const sf::View& view) const {
    // Получаем позицию мыши в координатах того же вида (view)
    sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel, view);

    // Верхняя координата поля
    float yTop = view.getCenter().y - size.y / 2.f;

    // Проверяем попадание курсора в границы поля
    sf::FloatRect bounds({ position.x, yTop }, { size.x, size.y });
    return bounds.contains(mousePos);
}

void Field::setSelectedElement(FieldElement* el) {
    for (auto& e : elements) {
        auto* item = dynamic_cast<ItemElement*>(e.get());
        if (item) item->selected = (e.get() == el);
    }
}
void Field::removeElementByLinkedObject(void* objPtr) {
    elements.erase(
        std::remove_if(elements.begin(), elements.end(),
            [objPtr](const std::unique_ptr<FieldElement>& el) {
                auto item = dynamic_cast<ItemElement*>(el.get());
                if (!item) return false;

                return std::visit(overloaded{
                    [objPtr](const std::shared_ptr<Point>& p){ return p.get() == objPtr; },
                    [objPtr](const std::shared_ptr<Line>& l){ return l.get() == objPtr; },
                    [objPtr](const std::shared_ptr<Polygon>& poly){ return poly.get() == objPtr; }
                }, item->linkedObject);
            }),
        elements.end()
    );
}