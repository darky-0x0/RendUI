#pragma once
#include "FieldElement.h"
#include "Primitive.hpp"



namespace RendUI {
    class PrimitivesManager;

    class ItemElement : public FieldElement {
    private:
        PrimitivesManager* manager = nullptr;

        void deleteLinkedObject(); // Удаление объекта из сцены 
    public:
        bool markedForDeletion = false; // Помечаем на удаление
        std::string iconPath;
        bool selected = false;
        float height = 30.f;
        std::variant<std::shared_ptr<Point>, std::shared_ptr<Line>, std::shared_ptr<Polygon>> linkedObject;

        std::function<void()> onClick;
        std::function<void()> onDelete;

        ItemElement(float h, std::shared_ptr<Point> p, PrimitivesManager* m = nullptr)
            : height(h), linkedObject(p) { 
            iconPath = "sources/icons/point.png";
            manager = m;
        }

        ItemElement(float h, std::shared_ptr<Line> l, PrimitivesManager* m = nullptr)
            : height(h), linkedObject(l) {
            iconPath = "sources/icons/line.png";
            manager = m;
        }

        ItemElement(float h, std::shared_ptr<Polygon> poly, PrimitivesManager* m = nullptr)
            : height(h), linkedObject(poly) {
            iconPath = "sources/icons/polygon.png";
            manager = m;
        }

        float getHeight() const override { return height; }

        void draw(sf::RenderWindow& window, const sf::Vector2f& position, float width) override {
            // фон элемента
            sf::RectangleShape bg({ width - 10.f, height });
            bg.setPosition(position);
            bg.setFillColor(selected ? sf::Color(80, 120, 200) : sf::Color(40, 40, 40));
            bg.setOutlineColor(sf::Color(180, 180, 200));
            bg.setOutlineThickness(1.f);
            window.draw(bg);

            // иконка
            static sf::Texture tex;
            if (tex.loadFromFile(iconPath)) {
                sf::Sprite sprite(tex);
                float iconSize = height * 0.7f;
                sprite.setScale({ iconSize / tex.getSize().x, iconSize / tex.getSize().y });
                sprite.setPosition({ position.x + 8.f, position.y + (height - iconSize) / 2 });
                window.draw(sprite);
            }

            // кнопка удаления
            sf::CircleShape del(6.f);
            del.setFillColor(sf::Color(255, 80, 80));
            del.setPosition({ position.x + width - 24.f, position.y + height / 3 });
            window.draw(del);
        }

        void handleEvent(const sf::Event& event, const sf::Vector2f& pos, float width, const sf::Vector2f& mousePos)
        {
            if (auto but = event.getIf<sf::Event::MouseButtonPressed>()) {
                if (but->button == sf::Mouse::Button::Left) {
                    // область удаления (в тех же координатах)
                    sf::FloatRect deleteRect({ pos.x + width - 24.f, pos.y + height / 3 }, { 12.f, 12.f });
                    if (deleteRect.contains(mousePos)) {
                        std::cout << "Корректное удаление";
                        deleteLinkedObject();
                        return;
                    }

                    // область всего элемента
                    sf::FloatRect itemRect(pos, { width - 10.f, height });
                    if (itemRect.contains(mousePos)) {
                        std::cout << "Корректное выделение";
                        selected = true;
                        if (onClick) onClick();
                    }
                }
            }
        }
    };

}

