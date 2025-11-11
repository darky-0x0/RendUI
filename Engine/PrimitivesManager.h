#pragma once
#include "Primitive.hpp"

namespace RendUI {

	class PrimitivesManager {
	public:
		// Добавление примитивов
		void addPoint(float x, float y);
		void addLine(Point a, Point b);
		void addPolygon(const std::vector<Point>& vertices);
		void clearAll();

		// Получение данных
		const std::vector<Point>& getPoints() const;
		const std::vector<Line>& getLines() const;
		const std::vector<Polygon>& getPolygons() const;

		// Удаление примитива, находящегося в радиусе от точки (x, y)
		bool deletePrimitiveAt(float x, float y);

		// Вспомогательная функция для вычисления расстояния между точками
		float distance(const Point& a, const Point& b);

		// Расстояние от точки p до отрезка (a, b)
		float distanceToSegment(const Point& p, const Point& a, const Point& b);

	private:
		std::vector<Point> points;
		std::vector<Line> lines;
		std::vector<Polygon> polygons;
	};
}

