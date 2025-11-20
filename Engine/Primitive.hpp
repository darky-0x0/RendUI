#include "pch.h"
#pragma once

namespace RendUI {
    class Renderer;

    struct Point {
        float x, y;
        sf::Color color = sf::Color::White;  // Добавляем цвет

        bool operator==(const Point& other) const {
            const float eps = 0.0001f;
            return std::fabs(x - other.x) < eps && std::fabs(y - other.y) < eps;
            // Цвет НЕ участвует в сравнении!
        }

        Point operator*(const Point& other) const {
            return { x * other.x, y * other.y };
        }
        Point operator*(const float k) const {
            return { x * k, y * k };
        }
        Point operator+(const Point& other) const {
            return { x + other.x, y + other.y };
        }
        Point operator-(const Point& other) const {
            return { x - other.x, y - other.y };
        }
    };

    struct Line {
        Point a, b;
        sf::Color color = sf::Color::White;  // Добавляем цвет

        bool operator==(const Line& other) const {
            return (a == other.a && b == other.b) || (a == other.b && b == other.a);
            // Цвет НЕ участвует в сравнении!
        }
    };

    struct Polygon {
        std::vector<Point> vertices;
        sf::Color color = sf::Color::White;  // Добавляем цвет

        bool operator==(const Polygon& other) const {
            if (vertices.size() != other.vertices.size()) return false;
            const size_t n = vertices.size();
            if (n == 0) return true;

            auto matches = [&](size_t shift, bool reverse) {
                for (size_t i = 0; i < n; ++i) {
                    const Point& pa = vertices[i];
                    const Point& pb = reverse ? other.vertices[(shift + n - i) % n]
                        : other.vertices[(shift + i) % n];
                    if (!(pa == pb)) return false;
                }
                return true;
                };

            for (size_t shift = 0; shift < n; ++shift) {
                if (vertices[0] == other.vertices[shift]) {
                    if (matches(shift, false) || matches(shift, true))
                        return true;
                }
            }
            return false;
        }
    };
}