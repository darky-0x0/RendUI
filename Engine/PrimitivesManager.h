#pragma once
#include "Primitive.hpp"
#include "Field.h"

namespace RendUI {

    class PrimitivesManager {
    public:
        // Добавление примитивов
        void addPoint(float x, float y);
        void addLine(Point a, Point b);
        void addPolygon(const std::vector<Point>& vertices);

        void deletePoint(std::shared_ptr<Point> p);
        void deleteLine(std::shared_ptr<Line> l);
        void deletePolygon(std::shared_ptr<Polygon> poly);

        void clearAll();

        // Получение данных
        std::vector<Point> getPoints() const;

        std::vector<Line> getLines() const;

        std::vector<Polygon> getPolygons() const;

        // Удаление примитива по координатам
        bool deletePrimitiveAt(float x, float y);

        void addElementList(Field* field) { elementList = field; }

    private:
        std::vector<std::shared_ptr<Point>> points;
        std::vector<std::shared_ptr<Line>> lines;
        std::vector<std::shared_ptr<Polygon>> polygons;
        Field* elementList = nullptr;

        float distance(const Point& a, const Point& b);
        float distanceToSegment(const Point& p, const Point& a, const Point& b);
    };

}

