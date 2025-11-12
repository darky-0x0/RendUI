#pragma once



namespace RendUI {

    class FieldElement {
    public:
        virtual ~FieldElement() = default;

        virtual float getHeight() const = 0;
        virtual void draw(sf::RenderWindow& window, const sf::Vector2f& position, float width) = 0;
        virtual void handleEvent(const sf::Event& event, const sf::Vector2f& position, float width, const sf::Vector2f& mousePos) {}
    };

}