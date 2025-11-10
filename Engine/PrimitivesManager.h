#pragma once
#include "Primitive.hpp"

namespace RendUI {

	class PrimitivesManager {
	public:
		// Добавление примитивов
		void addPoint(float x, float y);
		void addLine(Point a, Point b);
		void addPolygon(const std::vector<Point>& vertices);

		// Получение данных
		const std::vector<Point>& getPoints() const;
		const std::vector<Line>& getLines() const;
		const std::vector<Polygon>& getPolygons() const;

	private:
		std::vector<Point> points;
		std::vector<Line> lines;
		std::vector<Polygon> polygons;
	};
}

