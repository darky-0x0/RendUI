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

void RendUI::PrimitivesManager::clearAll() {
	points.clear();
	lines.clear();
	polygons.clear();
}

const std::vector<Point>& PrimitivesManager::getPoints() const { return points; }
const std::vector<Line>& PrimitivesManager::getLines() const { return lines; }
const std::vector<Polygon>& PrimitivesManager::getPolygons() const { return polygons; }



// ======================================================
// Удаление примитива, находящегося в радиусе от точки (x, y)
// ======================================================
bool PrimitivesManager::deletePrimitiveAt(float x, float y) {
    const float radius = 1.f; // радиус, в котором удаляем
    Point click{ x, y };

    // 1️ Проверяем точки
    for (auto it = points.begin(); it != points.end(); ++it) {
        if (distance(click, *it) <= radius) {
            points.erase(it);
            return true;
        }
    }

    // 2️ Проверяем линии
    for (auto it = lines.begin(); it != lines.end(); ++it) {
        if (distanceToSegment(click, it->a, it->b) <= radius) {
            lines.erase(it);
            return true;
        }
    }

    // 3️ Проверяем полигоны
    for (auto pit = polygons.begin(); pit != polygons.end(); ++pit) {
        for (auto& edge : pit->vertices) {
            if (distanceToSegment(click, edge.a, edge.b) <= radius) {
                polygons.erase(pit);
                return true;
            }
        }
    }

    return false; // ничего не удалили
}




// Вспомогательная функция для вычисления расстояния между точками
float PrimitivesManager::distance(const Point& a, const Point& b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

// Расстояние от точки p до отрезка (a, b)
float PrimitivesManager::distanceToSegment(const Point& p, const Point& a, const Point& b) {
    sf::Vector2f ap(p.x - a.x, p.y - a.y);
    sf::Vector2f ab(b.x - a.x, b.y - a.y);
    float ab2 = ab.x * ab.x + ab.y * ab.y;
    float t = (ab2 == 0) ? 0.f : (ap.x * ab.x + ap.y * ab.y) / ab2;
    t = std::clamp(t, 0.f, 1.f);
    sf::Vector2f proj(a.x + ab.x * t, a.y + ab.y * t);
    return std::sqrt((p.x - proj.x) * (p.x - proj.x) + (p.y - proj.y) * (p.y - proj.y));
}