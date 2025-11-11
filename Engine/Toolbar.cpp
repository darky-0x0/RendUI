#include "pch.h"
#include "Toolbar.h"



namespace RendUI {

    Toolbar::Toolbar(const sf::Vector2f& size, float cornerRadius)
        : background(size, cornerRadius, 8)
    {
        background.setFillColor(sf::Color(45, 45, 45, 230));
        background.setOutlineThickness(2.f);
        background.setOutlineColor(sf::Color(80, 80, 80));

        // Позиция будет обновляться динамически
        background.setPosition({ 0.f, 0.f });
    }

    void Toolbar::addTool(ToolType type, const std::string& iconFile, const sf::Vector2f& position) {
        tools.emplace_back(type, iconFile, position);
    }

    void Toolbar::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
        hoveredToolIndex = -1;

        if (const auto* moved = event.getIf<sf::Event::MouseMoved>()) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            for (size_t i = 0; i < tools.size(); ++i) {
                if (tools[i].bounds.contains(mousePos)) {
                    hoveredToolIndex = static_cast<int>(i);
                    break;
                }
            }
        }

        if (const auto* released = event.getIf<sf::Event::MouseButtonPressed>()) {
            if (released->button != sf::Mouse::Button::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                for (size_t i = 0; i < tools.size(); ++i) {
                    if (tools[i].bounds.contains(mousePos)) {
                        selectedTool = tools[i].type;
                        break;
                    }
                }
            }
        }
    }

    void Toolbar::draw(sf::RenderWindow& window) {
        // Размер тулбара
        sf::Vector2f bgSize = background.getSize();

        // Центрирование по окну
        sf::Vector2f bgPos((window.getSize().x - bgSize.x) / 2.f, 10.f);
        background.setPosition(bgPos);

        // Рисуем фон
        window.draw(background);

        // Рисуем инструменты
        for (size_t i = 0; i < tools.size(); ++i) {
            auto& tool = tools[i];

            // Глобальная позиция для вычисления рамок
            sf::Vector2f globalPos = bgPos + tool.relativePos;
            tool.sprite->setPosition(globalPos);
            tool.bounds = tool.sprite->getGlobalBounds();

            // Подсветка при наведении
            if (static_cast<int>(i) == hoveredToolIndex) {
                sf::RectangleShape highlight({ tool.bounds.size.x + 8.f, tool.bounds.size.y + 8.f });
                highlight.setPosition({ tool.bounds.position.x- 4.f, tool.bounds.position.y - 4.f });
                highlight.setFillColor(sf::Color(255, 255, 255, 40));
                highlight.setOutlineThickness(1.f);
                highlight.setOutlineColor(sf::Color(180, 180, 180, 120));
                window.draw(highlight);
            }

            // Подсветка выбранного инструмента
            if (tool.type == selectedTool) {
                sf::RectangleShape selected({ tool.bounds.size.x + 8.f, tool.bounds.size.y + 8.f });
                selected.setPosition({ tool.bounds.position.x - 4.f, tool.bounds.position.y - 4.f });
                selected.setFillColor(sf::Color(100, 150, 255, 60));
                selected.setOutlineThickness(1.5f);
                selected.setOutlineColor(sf::Color(80, 130, 255));
                window.draw(selected);
            }

            // Отрисовка иконки
            tool.draw(window, bgPos);
        }
    }

} 