#pragma once
#include "Renderer.h"
#include "Input.h"
#include "Grid.h"
#include "Primitive.hpp"
#include "PrimitivesManager.h"


namespace RendUI {
	class Engine {
	public:
		Engine(int width, int height, const std::string& title);
		void run();
		
		// Ќовые методы дл€ добавлени€ примитивов
		void addPoint(float x, float y);
		void addLine(Point a, Point b);
		void addPolygon(const std::vector<Point>& vertices);

	private:
		Renderer renderer;
		Input input;
		Grid grid;
		PrimitivesManager primitives;
		bool running = false;
	};
}


