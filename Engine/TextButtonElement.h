#pragma once
#include "FieldElement.h"




namespace RendUI {
    class Engine;

    class TextButtonElement : public FieldElement {
    public:
        // шрифт передаём ссылкой, чтобы sf::Text всегда имел валидный шрифт
        TextButtonElement(const std::string& textStr, float fieldWidth, const sf::Font& fontRef, std::function<void()> callback, Engine* enigne);

        void draw(sf::RenderWindow& window, const sf::Vector2f& position, float contentWidth) override;
        void handleEvent(const sf::Event& event, const sf::Vector2f& position, float contentWidth, const sf::Vector2f& mousePos) override;
        float getHeight() const override { return background.getSize().y; }

        std::wstring stringToWstring(const std::string& str);

        // Выделен ли элемент
        bool selected = false;
    private:
        Engine* enginePtr;

        void wrapText(float maxWidth);

        sf::RectangleShape background;
        sf::Text text;
        std::function<void()> callback;
        float padding = 8.f;
    };
}