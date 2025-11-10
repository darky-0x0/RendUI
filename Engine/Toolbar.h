#pragma once


namespace RendUI {
	enum class ToolType {
		None,
		Point,
		Line,
		Polygon,
		Erase,
		Clear
	};

	struct Tool {
		ToolType type;
		sf::Texture texture;
		sf::Sprite sprite;
		bool hovered = false;
		bool selected = false;
	};

	class Toolbar {
	public:
		Toolbar(float width, float height);

		void addTool(ToolType type, const std::string& iconFile, const sf::Vector2f& position);
		void draw(sf::RenderWindow& window);
	/*	void h*/

		ToolType getCurrentTool() const { return currentTool; }

	private:
		sf::RectangleShape background;
		sf::Color bgColor = sf::Color(50, 50, 50, 200);
		sf::Color outlineColor = sf::Color::White;
		float cornerRadius = 10.f;

		std::vector<Tool> tools;
		ToolType currentTool = ToolType::None;

		// Рамка подсветки
		sf::RectangleShape hoverRect;
		sf::RectangleShape selectedRect;
		sf::Color hoverColor = sf::Color(255, 255, 255, 150);
		sf::Color activeColor = sf::Color(0, 255, 0, 150);
	};
}


