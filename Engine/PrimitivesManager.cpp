#include "pch.h"
#include "PrimitivesManager.h"


using namespace RendUI;

void PrimitivesManager::addPoint(float x, float y) {
	points.push_back({ x, y });
}

void PrimitivesManager::addLine(Point a, Point b) {
	lines.push_back({ a, b });
}

void PrimitivesManager::addPolygon(const std::vector<Point>& vertices) {
	Polygon poly;
	for (size_t i = 0; i < vertices.size(); ++i) {
		Point a = vertices[i];
		Point b = vertices[(i + 1) % vertices.size()]; // замыкаем
		poly.vertices.push_back({ a, b });
	}
	polygons.push_back(poly);
}

const std::vector<Point>& PrimitivesManager::getPoints() const { return points; }
const std::vector<Line>& PrimitivesManager::getLines() const { return lines; }
const std::vector<Polygon>& PrimitivesManager::getPolygons() const { return polygons; }