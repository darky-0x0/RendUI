#pragma once

#include "RoundedRectangleShape.h"
#include "ViewState.h"


namespace RendUI {

    enum class ToolType {
        None,
        DrawPoint,
        // Можно добавить другие инструменты позже
    };

    class Tool {
    public:
        ToolType type;
        std::unique_ptr<sf::Texture> texture;
        std::unique_ptr<sf::Sprite> sprite;
        sf::FloatRect bounds;
        sf::Vector2f relativePos; // позиция внутри тулбара

        Tool(ToolType t, const std::string& iconFile, const sf::Vector2f& relPos)
            : type(t), relativePos(relPos)
        {
            texture = std::make_unique<sf::Texture>();
            if (!texture->loadFromFile(iconFile)) {
                std::cout << "Не удалось загрузить иконку: " << iconFile << std::endl;
                exit(1);
            }

            sprite = std::make_unique<sf::Sprite>(*texture);
            sprite->setScale({ 0.3f, 0.3f });
            sprite->setPosition(relPos); // пока ставим как есть
            bounds = sprite->getGlobalBounds();
        }

        void draw(sf::RenderWindow& window, const sf::Vector2f& toolbarPos) {
            if (sprite) {
                sprite->setPosition(toolbarPos + relativePos); // глобальная позиция = тулбар + смещение
                window.draw(*sprite);
            }
        }
    };

    class Toolbar {
    public:
        Toolbar(const sf::Vector2f& size, float cornerRadius);

        void addTool(ToolType type, const std::string& iconFile, const sf::Vector2f& position);
        void draw(sf::RenderWindow& window);
        void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

        ToolType getSelectedTool() const { return selectedTool; }

    private:
        RoundedRectangleShape background;
        std::vector<Tool> tools;
        ToolType selectedTool = ToolType::None;
        int hoveredToolIndex = -1;
    };

}