#pragma once
#include "Renderer.h"
#include "Input.h"
#include "Primitive.hpp"
#include "PrimitivesManager.h"
#include "ViewState.h"
#include "CoordinateSystem.h"
#include "Toolbar.h"
#include "Field.h"
#include "ItemElement.h"


namespace RendUI {
	class Engine {
	public:
		Engine(int width, int height, const std::string& title);
		void run();
		
		// Новые методы для добавления примитивов
		void addPoint(float x, float y);
		void addLine(Point a, Point b);
		void addPolygon(const std::vector<Point>& vertices);
		void deleteAllPrimitives();
		

		void handleLineTool(float x, float y);
		void handlePolygonTool(float x, float y);
		void handleDeleteTool(float x, float y);

	private:
		Renderer renderer;
		ViewState viewState;
		ViewState UIViewState;
		Input input;
		Toolbar toolbar;
		ToolType currentTool = ToolType::Point;
		CoordinateSystem coordSystem;
		PrimitivesManager primitives;
		bool running = false;
		float zoomFactor = 1.1f;
		sf::Vector2f lastMousePos;
		bool rightMousePressed = false;
		PrimitivesManager tempPrimitives; // для временных примитивов (например, рисование линии)
		bool drawingInProgress = false; // для инструментов, требующих нескольких кликов
		sf::CircleShape previewPoint; // Точка, следуемая за курсором
		bool showPreview = false;

		Field leftField; // Левая панель
	};
}


