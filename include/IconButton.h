#pragma once



namespace RendUI {

    class IconButton {
    public:
        IconButton(
            std::string iconPath,
            const sf::Vector2f& position,
            std::function<void()> onClick);

        void draw(sf::RenderWindow& window, sf::View& view, int iconNum);
        void handleEvent(const sf::Event& event, const sf::Vector2f& mousePos);
        void setSize(const sf::Vector2f& size);
        sf::Vector2f getSize() const { return background.getSize(); }

        bool isMouseOver(sf::RenderWindow& window, const sf::View& view) const;

        bool isMouse(const sf::Vector2f& mousePos) const;

    private:
        sf::RectangleShape background;
        std::function<void()> callback;
        bool hovered = false;

        std::string iconPathG;

        void updateColor();
    };

}