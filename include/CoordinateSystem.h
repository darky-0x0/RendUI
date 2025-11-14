#pragma once


#include <SFML/Graphics.hpp>


namespace RendUI {

	class CoordinateSystem {
	public:
		CoordinateSystem(float step = 50.f);
		float getStep() const { return step; }

		void draw(sf::RenderWindow& window, const sf::View& view);

	private:
		float step;
		sf::Color gridColor;
		sf::Color axisColor;
		sf::Font font;
	};
}