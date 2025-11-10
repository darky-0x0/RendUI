#include "pch.h"
#include "Grid.h"


using namespace RendUI;

Grid::Grid(float step) : step(step) {}

void Grid::draw(Renderer& renderer) {
	sf::Color gridColor(60, 60, 60);

	renderer.drawGrid(step, gridColor);
}
