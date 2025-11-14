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
#include "NotificationManager.h"
#include "TextButtonElement.h"
#include "IconButton.h"


namespace RendUI {
	class Engine {
	public:
		Engine(int width = 800, int height = 600, const std::string& title = "RendUI Engine");
		void run();
		
		// Новые методы для добавления примитивов
		void addPoint(float x, float y);
		void addLine(Point a, Point b);
		void addPolygon(const std::vector<Point>& vertices);
		void deleteAllPrimitives();

		// Получение примитивов
		std::vector<Point> getPoints() { return primitives.getPoints(); };
		std::vector<Line> getLines() { return primitives.getLines(); };
		std::vector<Polygon> getPolygons() { return primitives.getPolygons(); };

		// Работа с уведомлениями
		void showNotification(const std::string& msg);
		
		// Работа с задачами
		void addTask(const std::string& msg, std::function<void()> funct);

		// Сохранение и загрузка
		void savePrimitivesToJson();
		void loadPrimitivesFromJson();

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
		Field rightField; // Правая панель


		// Временное хранение данных при создании примитива
		sf::Vector2f startLinePoint;
		std::vector<Point> polygonPoints;

		// Уведомления
		NotificationManager notifications;
		sf::Clock deltaClock;

		// Шрифт
		sf::Font fontMain;

		// Сохранение и загрузка
		std::unique_ptr<IconButton> saveButton;
		std::unique_ptr<IconButton> loadButton;

	};
}


