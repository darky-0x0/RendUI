#pragma once
#include "Renderer.h"
#include "Input.h"
#include "Primitive.hpp"
#include "PrimitivesManager.h"
#include "ViewState.h"
#include "CoordinateSystem.h"
#include "Toolbar.h"


namespace RendUI {
	class Engine {
	public:
		Engine(int width, int height, const std::string& title);
		void run();
		
		// Ќовые методы дл€ добавлени€ примитивов
		void addPoint(float x, float y);
		void addLine(Point a, Point b);
		void addPolygon(const std::vector<Point>& vertices);
		void deleteAllPrimitives();

	private:
		Renderer renderer;
		ViewState viewState;
		ViewState UIViewState;
		Input input;
		Toolbar toolbar;
		CoordinateSystem coordSystem;
		PrimitivesManager primitives;
		bool running = false;
		float zoomFactor = 1.1f;
		sf::Vector2f lastMousePos;
		bool rightMousePressed = false;
	};
}


