// Testing.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.


#include <iostream>
#include "Engine.h"

//==================================================================================================
//=			!!Подсказка подключения есть в соответсвующем txt файле корня репозитория!!			   =
//==================================================================================================
//=									Пространство имён - RendUI									   =
//==================================================================================================
//=											API команды											   =
//= 																							   =
//= Работа с примитивами:																		   =
//= -- engine.addPoint(float x, float y) - добавление точки										   =
//= -- engine.addLine({float x1, float y1},{float x2, float x2}) - добавление линии				   =
//= -- engine.addPolygon({float x1, float y1}, ..., {float xn, float yn}) - добавление полигона	   =
//= -- engine.addPoint(Point p) - добавление точки												   =
//= -- engine.addLine(Line l) - добавление линии												   =
//= -- engine.addPolygon(Polygon poly) - добавление полигона									   =
//= -- engine.addPoints(vector<Point>) - добавление массива точек								   =
//= -- engine.addLines(vector<Line>) - добавление массива линий									   =
//= -- engine.addPolygons(vector<Polygon>) - добавление массива полигонов						   =
//= -- engine.addPoint(float x, float y, sf::Color color) - добавление точки цвета color		   =
//= -- engine.addLine({float x1, float y1},{float x2, float x2}, sf::Color color) - добавление     =
//=    линии цвета color																		   =
//= -- engine.addPolygon({float x1, float y1}, ..., {float xn, float yn}, sf::Color color) -	   =
//=    добавление полигона цвета color															   =
//= -- primitive.color = sf::Color::<Цвет> - изменение цвета для конкретного примитива			   =
//= -- vector<Point> engine.getPoints() - возвращение копии вектора точек						   =
//= -- vector<Line> engine.getLines() - возвращение копии вектора линий							   =
//= -- vector<Polygon> engine.getPolygons() - возвращение копии вектора полигонов				   =
//= -- engine.deletePoints() - удаление точек													   =
//= -- engine.deleteLines() - удаление линий													   =
//= -- engine.deletePolygons() - удаление полигонов												   =
//= -- engine.deleteAllPrimitives() - удаление всех примитивов из памяти						   =
//= 																							   =
//= Интерфейс:																					   =
//= -- engine.showNotification(string msg) - вывод уведомления с содержимым msg.				   =
//= -- engine.addTask(string name, function functional) - создание задачи functional с именем name =
//=	-- engine.run() - запуск																	   =
//=																								   =
//==================================================================================================
//=									Рекомендации по созданию функционала						   =
//= 																							   =
//=	-- Создание отдельной функции для отдельных задач											   =
//= -- Пример:																					   =
//=		void testFunct(Engine& engine) {														   =
//=			engine.addTask("Hello мир2!", [&engine] {											   =
//=				std::cout << "Привет мир!\n";													   =
//=				engine.showNotification("Hello world!");										   =
//=				std::vector<Point> points = engine.getPoints();									   =
//=				std::cout << "Точка: " << points[0].x << ":" << points[0].y;					   =
//=			});																					   =
//=		 }																						   =
//=																								   =
//==================================================================================================


using namespace RendUI;

void testFunct(Engine& engine);
void testFunct2(Engine& engine);
void testFunct3(Engine& engine);

int main()
{
	setlocale(0, "");
	Engine engine(800, 600, "RendUI Engine Test");
	engine.addPoint(2.f, 1.f);
	Point p({10.f, 20.f});
	p.color = sf::Color::Black;
	engine.addPoint(p);
	engine.addLine({ 3.f, 3.f }, { 6.f, 6.f }, sf::Color::Yellow);
	engine.addPolygon({ {8.f, 8.f}, {10.f, 8.f}, {11.f, 10.f}, {9.f, 11.f} });
	engine.showNotification("Добро пожаловать в программу!");
	//engine.deletePoints();
	//engine.deleteLines();
	testFunct(engine);
	testFunct2(engine);
	testFunct3(engine);
	
	engine.run();
	return 0;
}


void testFunct(Engine& engine) {
	engine.addTask("Hello мир2!", [&engine] {
		auto ps = engine.getPoints();
		auto ls = engine.getLines();
		auto polys = engine.getPolygons();
		std::cout << "Привет мир!";
		engine.showNotification("Лан лан");
		std::vector<Point> points = engine.getPoints();
		std::cout << points[0].x << ":" << points[0].y;
		engine.deleteAllPrimitives();
	});
}

void testFunct2(Engine& engine) {
	engine.addTask("Добавить рандомные точки", [&engine] {
		float a = 0;
		float b = 10;
		std::vector<Point> points;

		for (int i = 0; i < 30; i++) {
			float x = a + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (b - a));
			float y = a + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (b - a));
			points.push_back({ x, y });
		}

		engine.addPoints(points);
		});
}

void testFunct3(Engine& engine) {
	engine.addTask("Удалить все точки", [&engine] {
		engine.deletePoints();
		});
}