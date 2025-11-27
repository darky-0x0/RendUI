#pragma once
#include "Primitive.hpp"
#include "Field.h"

namespace RendUI {

    class Engine;

    class PrimitivesManager {
    public:
        // Добавление примитивов
        void addPoint(float x, float y);
        void addPoint(float x, float y, sf::Color color);
        void addLine(Point a, Point b);
        void addLine(Point a, Point b, sf::Color color);
        void addPolygon(const std::vector<Point>& vertices);
        void addPolygon(std::vector<Point>& vertices, sf::Color color);

        void addPoint(const Point& point);
        void addLine(const Line& line);
        void addPolygon(Polygon& polygon);

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

