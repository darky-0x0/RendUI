#include "pch.h"    // PCH должен подключаться первым в .cpp
#include "Renderer.h"
#include "Primitive.hpp"


using namespace RendUI;


Renderer::Renderer(int weidth, int height, const std::string& title)
	: window(sf::RenderWindow(sf::VideoMode({ static_cast<unsigned int>(weidth), static_cast<unsigned int>(height) }), title)) {
	windowWidth = (float)weidth;
	windowHeight = (float)height;
}

void Renderer::clear() { window.clear(sf::Color(20, 20, 20)); }
void Renderer::display() { window.display(); }
bool Renderer::isOpen() const { return window.isOpen(); }
sf::RenderWindow& Renderer::getWindow() { return window; }



void Renderer::update(const PrimitivesManager& primitives) {
	const auto& points = primitives.getPoints();
	const auto& lines = primitives.getLines();
	const auto& polygons = primitives.getPolygons();

	for (const Point& p : points) { drawPoint(p); }
	for (const Line& l : lines) { drawLine(l); }
	for (const Polygon& poly : polygons) { drawPolygon(poly); }

}


void Renderer::drawGrid(float step, sf::Color gridColor) {
	sf::VertexArray lines(sf::PrimitiveType::Lines);

	for (float x = 0; x <= windowWidth; x += step) {
		lines.append(sf::Vertex{ {x, 0}, gridColor } );
		lines.append(sf::Vertex{ {x, windowHeight}, gridColor });
	}

	for (float y = 0; y <= windowHeight; y += step) {
		lines.append(sf::Vertex{ {0, y}, gridColor });
		lines.append(sf::Vertex{ {windowWidth, y}, gridColor });
	}

	window.draw(lines);

}


void Renderer::drawPoint(const Point& p, const float radius) {
	sf::CircleShape circle(radius);
	circle.setFillColor(sf::Color::White);
	// Центрируем круг по координатам точки
	circle.setPosition({ p.x - radius, p.y - radius });
	window.draw(circle);
}


void Renderer::drawLine(const Line& l) {
	sf::Vertex verts[2] = {
		sf::Vertex{ { l.a.x, l.a.y }, sf::Color::White},
		sf::Vertex{ { l.b.x, l.b.y }, sf::Color::White}
	};
	drawPoint(l.a, 4);
	drawPoint(l.b, 4);
	window.draw(verts, 2, sf::PrimitiveType::Lines);
}


void Renderer::drawPolygon(const Polygon& poly) {
	for (const Line& ln : poly.vertices) {
		drawLine(ln);
	}
}
