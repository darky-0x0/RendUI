#include "pch.h"
#pragma once


namespace RendUI {
	class Renderer;
	
	struct Point {
		float x, y;


		bool operator==(const Point& other) const {
			const float eps = 0.0001f;
			return std::fabs(x - other.x) < eps && std::fabs(y - other.y) < eps;
		}
        Point operator*(const Point& other) const {
            return { x * other.x, y * other.y };
        }
        Point operator*(const float k) const {
            return { x * k, y * k };
        }
	};
	
	struct Line {
		Point a, b;


		bool operator==(const Line& other) const {
			return (a == other.a && b == other.b) || (a == other.b && b == other.a);
		}
	};

	struct Polygon {
		std::vector<Point> vertices;


		bool operator==(const Polygon& other) const {
            if (vertices.size() != other.vertices.size()) return false;
            const size_t n = vertices.size();
            if (n == 0) return true;

            // Лямбда для проверки совпадения сдвига в прямом или обратном направлении
            auto matches = [&](size_t shift, bool reverse) {
                for (size_t i = 0; i < n; ++i) {
                    const Point& pa = vertices[i];
                    const Point& pb = reverse ? other.vertices[(shift + n - i) % n]
                        : other.vertices[(shift + i) % n];
                    if (!(pa == pb)) return false;
                }
                return true;
                };

            // Основная оптимизация: ищем совпадающую точку
            for (size_t shift = 0; shift < n; ++shift) {
                if (vertices[0] == other.vertices[shift]) {
                    // Если первая точка совпала, проверяем оба направления
                    if (matches(shift, false) || matches(shift, true))
                        return true;
                }
            }

            return false;
		}
	};
}