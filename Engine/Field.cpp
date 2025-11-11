#include "pch.h"
#include "Field.h"


using namespace RendUI;

Field::Field(const sf::Vector2f& pos, const sf::Vector2f& size)
    : position(pos), size(size), background(size, 12.f)
{
    background.setPosition(pos);
    background.setFillColor(bgColor);
    background.setOutlineThickness(1.5f);
    background.setOutlineColor(borderColor);

    scrollbar.setFillColor(sf::Color(180, 180, 180, 200));
    scrollbar.setSize({ scrollbarWidth, size.y });
}

void Field::addItem(const FieldItem& item) {
    items.push_back(item);
    totalContentHeight += item.height + 4.f;
}

void Field::clear() {
    items.clear();
    totalContentHeight = 0.f;
    scrollOffset = 0.f;
}

void Field::draw(sf::RenderWindow& window, ViewState& view) {
    float yCenter = view.getView().getCenter().y - size.y / 2.f;
	background.setPosition({position.x, yCenter});

    window.draw(background);

    float y = yCenter + 10.f - scrollOffset;

    for (auto& item : items) {
        // Фон элемента
        sf::RectangleShape itemBg({ size.x - scrollbarWidth - 10.f, item.height });
        itemBg.setPosition({ position.x + 10.f, y });
        itemBg.setFillColor(item.selected ? selectedColor : sf::Color::Black);
        itemBg.setOutlineColor(borderColor);
        itemBg.setOutlineThickness(1.f);
        window.draw(itemBg);

        // Иконка
        sf::Texture texture;
        if (!texture.loadFromFile(item.iconPath)) {
            std::cerr << "Ошибка: не удалось загрузить " << item.iconPath << "\n";
        }
        else {
            sf::Sprite icon(texture);
            float iconSize = item.height * 0.7f;
            icon.setScale({ iconSize / texture.getSize().x, iconSize / texture.getSize().y });
            icon.setPosition({ itemBg.getPosition().x + 8.f, y + (item.height - iconSize) / 2 });
            window.draw(icon);
        }

        // Кнопка удаления
        sf::CircleShape deleteBtn(6.f);
        deleteBtn.setFillColor(deleteColor);
        deleteBtn.setPosition({ itemBg.getPosition().x + itemBg.getSize().x - 14.f, y + item.height / 3 });
        window.draw(deleteBtn);

        y += item.height + 4.f;
    }

    // Полоса прокрутки
    if (totalContentHeight > size.y) {
        float scrollRatio = size.y / totalContentHeight;
        float scrollbarHeight = size.y * scrollRatio;

        float scrollbarY = position.y + (scrollOffset / totalContentHeight) * size.y;
        scrollbar.setPosition({ position.x + size.x - scrollbarWidth, scrollbarY });
        scrollbar.setSize({ scrollbarWidth, scrollbarHeight });
        window.draw(scrollbar);
    }
}

void Field::handleEvent(const sf::Event& event, const sf::RenderWindow& window, const sf::View& view) {
    // Конвертируем координаты мыши в координаты view
    sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel, view);

    float yCenter = view.getCenter().y - size.y / 2.f;

    if (const auto* wheel = event.getIf<sf::Event::MouseWheelScrolled>()) {
        if (totalContentHeight > size.y) {
            scrollOffset -= wheel->delta * 20.f;
            if (scrollOffset < 0) scrollOffset = 0;
            if (scrollOffset > totalContentHeight - size.y)
                scrollOffset = totalContentHeight - size.y;
        }
    }

    if (const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>()) {
        float y = yCenter + 5.f - scrollOffset;

        for (auto& item : items) {
            sf::FloatRect itemRect({ position.x + 5.f, y }, { size.x - scrollbarWidth - 10.f, item.height });
            sf::FloatRect deleteRect({ itemRect.position.x + itemRect.size.x - 14.f, itemRect.position.y + item.height / 3 }, { 12.f, 12.f });

            if (deleteRect.contains(mousePos)) {
                if (item.onDelete) item.onDelete();
                return;
            }

            if (itemRect.contains(mousePos)) {
                for (auto& i : items) i.selected = false;
                item.selected = true;
                if (item.onClick) item.onClick();
                return;
            }

            y += item.height + 4.f;
        }
    }
}


bool Field::isMouseOver(sf::RenderWindow& window, const sf::View& view) const {
    sf::View oldView = window.getView();
    // Устанавливаем вид, чтобы корректно получить позицию мыши в координатах окна
    window.setView(view);
    sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel);

    // Проверяем, попадает ли курсор в фон тулбара
    return background.getGlobalBounds().contains(mousePos);
    window.setView(oldView);
}