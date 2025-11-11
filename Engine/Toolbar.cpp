#include "pch.h"
#include "Toolbar.h"



using namespace RendUI;

// ==================== TOOL ====================

Tool::Tool(ToolType t, const std::string& iconFile, const sf::Vector2f& position) {
	type = t;
	texture = std::make_unique<sf::Texture>();
	if (!texture->loadFromFile(iconFile)) {
		std::cout << "Не удалось загрузить иконку: " << iconFile << std::endl;
		exit(1);
	}
	sprite = std::make_unique<sf::Sprite>(*texture);
	sprite->setScale({ 0.28f, 0.28f });
	sprite->setPosition(position);
	bounds = sprite->getGlobalBounds();
}

void Tool::draw(sf::RenderWindow& window) {
	if (sprite)
		window.draw(*sprite);
}

void Tool::draw(sf::RenderWindow& window, const sf::Vector2f& toolbarPos) {
	if (!sprite) return;
	sprite->setPosition(toolbarPos + relativePos);
	window.draw(*sprite);
	bounds = sprite->getGlobalBounds();
}


// ==================== TOOLBAR ====================

Toolbar::Toolbar() {
	background.setFillColor(sf::Color(30, 30, 30, 200));
	background.setOutlineThickness(1.f);
	background.setOutlineColor(sf::Color(80, 80, 80, 255));
}

void Toolbar::addTool(ToolType type, const std::string& iconFile) {
	tools.emplace_back(type, iconFile, sf::Vector2f(0.f, 0.f)); // позиция задастся позже
	updateLayout();
}

void Toolbar::updateLayout() {
	if (tools.empty()) return;

	// Расчёт общей ширины тулбара
	float totalWidth = padding + (iconSize + padding) * tools.size();
	float totalHeight = iconSize + padding * 2.f;

	background.setSize({ totalWidth, totalHeight });

	// Позиции инструментов относительно тулбара
	float x = padding;
	float y = padding;
	for (auto& tool : tools) {
		tool.relativePos = { x, y };
		x += iconSize + padding;
	}
}

void Toolbar::draw(sf::RenderWindow& window) {
	sf::Vector2f bgSize = background.getSize();
	sf::Vector2f bgPos((window.getSize().x - bgSize.x) / 2.f, topOffset);
	background.setPosition(bgPos);

	// Рисуем фон тулбара
	window.draw(background);

	// Сначала подсветка, потом иконки
	for (size_t i = 0; i < tools.size(); ++i) {
		auto& tool = tools[i];
		sf::Vector2f iconPos = bgPos + tool.relativePos;
		sf::FloatRect rect({ iconPos.x, iconPos.y }, { iconSize, iconSize });

		//// Подсветка при наведении
		//if ((int)i == hoveredToolIndex) {
		//	sf::RectangleShape highlight({ iconSize + 8.f, iconSize + 8.f });
		//	highlight.setPosition({ iconPos.x - 4.f, iconPos.y - 4.f });
		//	highlight.setFillColor(sf::Color(255, 255, 255, 40));
		//	highlight.setOutlineThickness(1.f);
		//	highlight.setOutlineColor(sf::Color(180, 180, 180, 120));
		//	window.draw(highlight);
		//}

		// Подсветка выбранного инструмента
		if (tool.type == selectedTool) {
			sf::RectangleShape selected({ iconSize + 8.f, iconSize + 8.f });
			selected.setPosition({ iconPos.x - 4.f, iconPos.y - 4.f });
			selected.setFillColor(sf::Color(100, 150, 255, 60));
			selected.setOutlineThickness(1.5f);
			selected.setOutlineColor(sf::Color(80, 130, 255));
			window.draw(selected);
		}
	}

	// Отрисовываем иконки (после подсветки)
	for (auto& tool : tools) {
		tool.draw(window, bgPos);
	}
}


void Toolbar::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
	hoveredToolIndex = -1;

	// Получаем позицию тулбара (чтобы правильно вычислить координаты иконок)
	sf::Vector2f bgSize = background.getSize();
	sf::Vector2f bgPos((window.getSize().x - bgSize.x) / 2.f, topOffset);

	//// Проверка наведения
	//if (const auto* moved = event.getIf<sf::Event::MouseMoved>()) {
	//	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	//	for (size_t i = 0; i < tools.size(); ++i) {
	//		auto& tool = tools[i];
	//		sf::FloatRect rect = tool.bounds;
	//		rect.position.x = bgPos.x + tool.relativePos.x;
	//		rect.position.y = bgPos.y + tool.relativePos.y;
	//		if (rect.contains(mousePos)) {
	//			hoveredToolIndex = static_cast<int>(i);
	//			break;
	//		}
	//	}
	//}

	// Обработка клика
	if (const auto* click = event.getIf<sf::Event::MouseButtonPressed>()) {
		if (click->button == sf::Mouse::Button::Left) {
			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			for (size_t i = 0; i < tools.size(); ++i) {
				auto& tool = tools[i];
				sf::FloatRect rect = tool.bounds;
				rect.position.x = bgPos.x + tool.relativePos.x;
				rect.position.y = bgPos.y + tool.relativePos.y;
				if (rect.contains(mousePos)) {
					selectedTool = tool.type;
					break;
				}
			}
		}
	}
}


bool Toolbar::isMouseOver(sf::RenderWindow& window, const sf::View& view) const {
	sf::View oldView = window.getView();
	// Устанавливаем вид, чтобы корректно получить позицию мыши в координатах окна
	window.setView(view);
	sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
	sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel);

	// Проверяем, попадает ли курсор в фон тулбара
	return background.getGlobalBounds().contains(mousePos);
	window.setView(oldView);
}

