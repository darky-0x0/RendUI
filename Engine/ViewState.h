#pragma once
#include <SFML/Graphics.hpp>


namespace RendUI {
	class ViewState
	{
	public:
		ViewState(float width, float height);

		void move(float offsetX, float offsetY);
		void zoom(float factor);
		void resize(sf::RenderWindow& window);
		void resetOffset();
		void applyTo(sf::RenderWindow& window);

		float getZoom() const { return zoomLevel; }
		sf::Vector2f getOffset() const { return offset; }

	private:
		sf::Vector2f offset;
		float zoomLevel;
		sf::View view;
		float width;
		float height;
		sf::Vector2f initialCenter;
		sf::Vector2f initialSize;
	};
}

