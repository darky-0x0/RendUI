#pragma once

#include <functional>
#include "RoundedRectangleShape.h"
#include "ViewState.h"
#include "FieldElement.h"
#include "ItemElement.h"
#include "TextButtonElement.h"

namespace RendUI {

    class Field {
    public:
        Field(int positionFlag, const sf::Vector2f& size);

        // Шаблонный метод добавления элемента (определение здесь — шаблон должен быть в заголовке)
        template <typename T, typename... Args>
        void addElement(Args&&... args) {
            static_assert(std::is_base_of<FieldElement, T>::value, "T must derive from FieldElement");
            auto el = std::make_unique<T>(std::forward<Args>(args)...);
            totalContentHeight += el->getHeight() + elementSpacing;
            elements.push_back(std::move(el));
        }

        // Обновляем, удаляя лишние элементы
        void update();

        // Добавить уже созданный элемент
        void addRawElement(std::unique_ptr<FieldElement>&& el);

        // Очистить
        void clear();

        // Отрисовка и события
        void draw(sf::RenderWindow& window, const sf::View& view);
        void handleEvent(const sf::Event& event, sf::RenderWindow& window, const sf::View& view);

        // Опционально: определить, находится ли мышь над полем (в координатах даного view)
        bool isMouseOver(const sf::RenderWindow& window, const sf::View& view) const;

        void removeElementByLinkedObject(void* objPtr); // Удаление объекта из списка

        void removeAllElements();

        void setSelectedElementItems(FieldElement* el); // новый метод
        void setSelectedElementText(FieldElement* el);

        sf::Vector2f getSize() { return size; };

    private:
        // Позиция
        int positionFlag = 0;
        // Отступ
        float margine = 10.f;

        // визуальные параметры
        RoundedRectangleShape background;
        sf::Vector2f position;
        sf::Vector2f size;

        // содержимое
        std::vector<std::unique_ptr<FieldElement>> elements;
        float elementSpacing = 4.f;

        // прокрутка
        float scrollOffset = 0.f;
        float totalContentHeight = 0.f;
        float scrollbarWidth = 10.f;

        // drag state
        bool draggingScrollbar = false;
        float dragStartY = 0.f;
        float initialScrollOffset = 0.f;

        // drawable
        sf::RectangleShape scrollbar;

        // стили
        sf::Color bgColor = sf::Color(60, 60, 60);
        sf::Color borderColor = sf::Color(180, 180, 200);
    };

}