#include "pch.h"
#include "PrimitivesManager.h"
#include "Field.h"


using namespace RendUI;

void PrimitivesManager::addPoint(float x, float y) {
    // Проверка на дубликат
    for (auto& sp : points) {
        if (sp && sp->x == x && sp->y == y)
            return; // дубликат найден, не добавляем
    }

    Point p({ x, y });
    auto sp = std::make_shared<Point>(p);
    points.push_back(sp);

    if (elementList)
        elementList->addElement<ItemElement>(40.f, sp, this); // передаем shared_ptr
}

void PrimitivesManager::addLine(Point a, Point b) {
    if (a.x == b.x && a.y == b.y) {
        addPoint(a.x, a.y);
    }
    else {
        // Проверка на дубликат (учитываем направление линии)
        for (auto& sp : lines) {
            if (!sp) continue;
            if ((sp->a.x == a.x && sp->a.y == a.y && sp->b.x == b.x && sp->b.y == b.y) ||
                (sp->a.x == b.x && sp->a.y == b.y && sp->b.x == a.x && sp->b.y == a.y))
                return; // дубликат найден
        }

        Line l({ a, b });
        auto sp = std::make_shared<Line>(l);
        lines.push_back(sp);

        if (elementList)
            elementList->addElement<ItemElement>(40.f, sp, this);
    }
}

void PrimitivesManager::addPolygon(const std::vector<Point>& vertices) {
    if (vertices.size() == 3 && vertices[0].x == vertices[1].x && vertices[0].y == vertices[1].y && vertices[0].x == vertices[2].x && vertices[0].y == vertices[2].y) {
        addPoint(vertices[0].x, vertices[0].y);
    }
    else if(vertices.size() == 3 && vertices[0].x == vertices[2].x && vertices[0].y == vertices[2].y && (vertices[0].x != vertices[1].x || vertices[0].y != vertices[1].y)) {
        addLine(vertices[0], vertices[1]);
    }
    else {
        // Проверка на дубликат: простое сравнение вершин
        for (auto& sp : polygons) {
            if (!sp || sp->vertices.size() != vertices.size()) continue;

            bool same = true;
            for (size_t i = 0; i < vertices.size(); ++i) {
                if (!(sp->vertices[i].a.x == vertices[i].x && sp->vertices[i].a.y == vertices[i].y &&
                    sp->vertices[i].b.x == vertices[(i + 1) % vertices.size()].x &&
                    sp->vertices[i].b.y == vertices[(i + 1) % vertices.size()].y)) {
                    same = false;
                    break;
                }
            }
            if (same) return; // дубликат найден
        }

        auto sp = std::make_shared<Polygon>();
        for (size_t i = 0; i < vertices.size(); ++i) {
            Point a = vertices[i];
            Point b = vertices[(i + 1) % vertices.size()];
            sp->vertices.push_back({ a, b });
        }
        polygons.push_back(sp);

        if (elementList)
            elementList->addElement<ItemElement>(40.f, sp, this);
    }
}

// Удаление по shared_ptr
void PrimitivesManager::deletePoint(std::shared_ptr<Point> p) {
    points.erase(std::remove(points.begin(), points.end(), p), points.end());
}

void PrimitivesManager::deleteLine(std::shared_ptr<Line> l) {
    lines.erase(std::remove(lines.begin(), lines.end(), l), lines.end());
}

void PrimitivesManager::deletePolygon(std::shared_ptr<Polygon> poly) {
    polygons.erase(std::remove(polygons.begin(), polygons.end(), poly), polygons.end());
}

void PrimitivesManager::clearAll() {
    points.clear();
    lines.clear();
    polygons.clear();
}

// ======================================================
// Удаление примитива, находящегося в радиусе от точки (x, y)
// ======================================================
bool PrimitivesManager::deletePrimitiveAt(float x, float y) {
    const float radius = 1.f;
    Point click{ x, y };

    // Проверяем точки
    for (auto it = points.begin(); it != points.end(); ++it) {
        if (distance(click, **it) <= radius) {
            if (elementList) // <-- Field
                elementList->removeElementByLinkedObject(it->get());
            points.erase(it);
            return true;
        }
    }

    // Проверяем линии
    for (auto it = lines.begin(); it != lines.end(); ++it) {
        if (distanceToSegment(click, (*it)->a, (*it)->b) <= radius) {
            if (elementList)
                elementList->removeElementByLinkedObject(it->get());
            lines.erase(it);
            return true;
        }
    }

    // Проверяем полигоны
    for (auto it = polygons.begin(); it != polygons.end(); ++it) {
        for (auto& edge : (*it)->vertices) {
            if (distanceToSegment(click, edge.a, edge.b) <= radius) {
                if (elementList)
                    elementList->removeElementByLinkedObject(it->get());
                polygons.erase(it);
                return true;
            }
        }
    }
    return false;
}

// Вспомогательные функции
float PrimitivesManager::distance(const Point& a, const Point& b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

float PrimitivesManager::distanceToSegment(const Point& p, const Point& a, const Point& b) {
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    if (dx == 0 && dy == 0)
        return distance(p, a);

    float t = ((p.x - a.x) * dx + (p.y - a.y) * dy) / (dx * dx + dy * dy);
    t = std::clamp(t, 0.f, 1.f);
    Point proj{ a.x + t * dx, a.y + t * dy };
    return distance(p, proj);
}

std::vector<Point> PrimitivesManager::getPoints() const {
    std::vector<Point> res;
    res.reserve(points.size());
    for (auto& sp : points) {
        if (sp) res.push_back(*sp);
    }
    return res;
}

std::vector<Line> PrimitivesManager::getLines() const {
    std::vector<Line> res;
    res.reserve(lines.size());
    for (auto& sp : lines) {
        if (sp) res.push_back(*sp);
    }
    return res;
}

std::vector<Polygon> PrimitivesManager::getPolygons() const {
    std::vector<Polygon> res;
    res.reserve(polygons.size());
    for (auto& sp : polygons) {
        if (sp) res.push_back(*sp);
    }
    return res;
}