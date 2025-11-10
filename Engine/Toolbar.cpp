#include "pch.h"
#include "Toolbar.h"



using namespace RendUI;


Toolbar::Toolbar(float width, float height) {
	background.setSize({ width, height });
	background.setFillColor(bgColor); // Тёмная полупрозрачная
	background.setPosition({ 0, 0 });
	background.setOutlineColor(outlineColor);
	background.setOutlineThickness(2);
	// Скруглить?

	// Подсветка
	hoverRect.setFillColor(sf::Color::Transparent);
	hoverRect.setOutlineColor(hoverColor);
	hoverRect.setOutlineThickness(2.f);

	selectedRect.setFillColor(sf::Color::Transparent);
	selectedRect.setOutlineColor(activeColor);
	selectedRect.setOutlineThickness(2.f);
}


void Toolbar::addTool(ToolType type, const std::string& iconFile, const sf::Vector2f& position) {
	tools.emplace_back(Tool{ type, sf::Texture(), sf::Sprite() });

}

void Toolbar::draw(sf::RenderWindow& window) {

}


void Toolbar::processClick(sf::Vector2f mousePos) {

}


void Toolbar::processHover(sf::Vector2f mousePos) {

}
