#pragma once



namespace RendUI {
    class Notification {
    public:
        Notification(const std::string& msg, const sf::Font& font, float windowWidth, float windowHeight);

        void update(float dt);
        void draw(sf::RenderWindow& window, const sf::View& view, float windowWidth, float windowHeight);
        bool isFinished() const { return finished; }

    private:
        sf::RectangleShape background;
        sf::Text text;
        sf::Font font;
        float lifetime;
        bool finished;
        sf::Vector2f position;

        // Размеры
        float height;
        float width;

        // Отступ
        float padding = 16.f;

        void updatePosition(float windowWidth, float windowHeight);

        std::wstring stringToWstring(const std::string& str);
    };
}