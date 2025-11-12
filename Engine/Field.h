#pragma once

#include <functional>
#include "RoundedRectangleShape.h"
#include "ViewState.h"

namespace RendUI {

    struct FieldItem {
        std::string iconPath;              // путь к иконке
        float height;                      // высота элемента
        bool selected = false;             // выделен ли элемент
        std::function<void()> onClick;     // действие при клике
        std::function<void()> onDelete;    // действие при удалении
    };

    class Field {
    private:
        RoundedRectangleShape background;  // фон поля
        sf::Vector2f position;
        sf::Vector2f size;

        float scrollOffset = 0.f;
        float totalContentHeight = 0.f;
        float scrollbarWidth = 10.f;
        float initialScrollOffset = 0.f;

        bool draggingScrollbar = false;
        float dragStartY = 0.f;
        float scrollStartOffset = 0.f;

        std::vector<FieldItem> items;
        sf::RectangleShape scrollbar;

        sf::Color bgColor = sf::Color(60, 60, 60);
        sf::Color borderColor = sf::Color(180, 180, 200);
        sf::Color selectedColor = sf::Color(190, 210, 255);
        sf::Color deleteColor = sf::Color(255, 80, 80);

    public:
        Field(const sf::Vector2f& pos, const sf::Vector2f& size);
        void addItem(const FieldItem& item);
        void clear();
        void draw(sf::RenderWindow& window, ViewState& view);
        void handleEvent(const sf::Event& event, const sf::RenderWindow& window, const sf::View& view);

        bool isMouseOver(sf::RenderWindow& window, const sf::View& view) const;
    };

}