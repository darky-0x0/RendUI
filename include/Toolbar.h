#pragma once

#include "RoundedRectangleShape.h"
#include "ViewState.h"


namespace RendUI {

	enum class ToolType {
		None,
		Point,
		Line,
		Polygon,
		Delete,
		Clear
	};

	class Tool {
	public:
		ToolType type;
		std::unique_ptr<sf::Texture> texture;
		std::unique_ptr<sf::Sprite> sprite;
		sf::FloatRect bounds;
		sf::Vector2f relativePos;

		Tool(ToolType t, const std::string& iconFile, const sf::Vector2f& position);

		void draw(sf::RenderWindow& window);
		void draw(sf::RenderWindow& window, const sf::Vector2f& toolbarPos);
	};


	class Toolbar {
	private:
		std::vector<Tool> tools;
		sf::RectangleShape background;

		float padding = 10.f;
		float iconSize = 32.f;
		float topOffset = -5.f; // отступ сверху окна

		int hoveredToolIndex = -1;
		ToolType selectedTool = ToolType::Point;

	public:
		Toolbar();

		void addTool(ToolType type, const std::string& iconFile);
		void updateLayout();
		void draw(sf::RenderWindow& window);
		void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

		bool isMouseOver(sf::RenderWindow& window, const sf::View& view) const;

		ToolType getSelectedTool() const { return selectedTool; }
	};
}
