#include "pch.h"
#include "IconButton.h"


using namespace RendUI;

IconButton::IconButton(std::string iconPath, const sf::Vector2f& position, std::function<void()> onClick)
    : callback(onClick)
{
    background.setSize({ 40.f, 40.f });
    background.setPosition(position);
    background.setFillColor(sf::Color(50, 50, 50));
    background.setOutlineThickness(1.f);
    background.setOutlineColor(sf::Color::White);



    iconPathG = iconPath;
}

void IconButton::draw(sf::RenderWindow& window, sf::View& view, int iconNum)
{
    float yPosition = 5;
    float xPosition = (iconNum == 1 ? 5.f : 55.f);
    sf::Vector2f position = { xPosition, yPosition };

    background.setPosition(position);
    
    window.draw(background);
    
    static sf::Texture tex;
    if (tex.loadFromFile(iconPathG)) {
        sf::Sprite sprite(tex);
        sprite.setScale({ 0.5f, 0.5f }); // уменьшаем иконку
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
        sf::Vector2f pos = { position.x + 6.f, position.y + 6.f };
        background.setPosition(pos);
        sprite.setPosition({ pos.x + 14.f, pos.y + 14.f });

        sprite.setScale({ 0.3, 0.3 });
        window.draw(sprite);
    }
}

void IconButton::handleEvent(const sf::Event& event, const sf::Vector2f& mousePos)
{
    hovered = isMouse(mousePos);
    updateColor();

    if (const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouse->button == sf::Mouse::Button::Left && hovered && callback)
            callback();
    }
}

void IconButton::updateColor()
{
    background.setFillColor(hovered ? sf::Color(90, 90, 120) : sf::Color(50, 50, 50));
}


void IconButton::setSize(const sf::Vector2f& size) {
    background.setSize(size);
}

bool IconButton::isMouseOver(sf::RenderWindow& window, const sf::View& view) const {
    sf::View oldView = window.getView();
    // Устанавливаем вид, чтобы корректно получить позицию мыши в координатах окна
    window.setView(view);
    sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel);

    // Проверяем, попадает ли курсор в фон тулбара
    return background.getGlobalBounds().contains(mousePos);
    window.setView(oldView);
}

bool IconButton::isMouse(const sf::Vector2f& mousePos) const {
    return background.getGlobalBounds().contains(mousePos);
}