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
		void resizeUI(sf::RenderWindow& window);
		void resetOffset();
		void applyTo(sf::RenderWindow& window);
		void setView(float width, float height) { view.setSize({ width, height}); }

		float getZoom() const { return zoomLevel; }
		sf::Vector2f getOffset() const { return offset; }
		sf::View& getView() { return view; }

	private:
		sf::View view;
		sf::Vector2f offset;
		float zoomLevel;
		float width = 0.f;
		float height = 0.f;
		sf::Vector2f initialCenter;
		sf::Vector2f initialSize;
	};
}

