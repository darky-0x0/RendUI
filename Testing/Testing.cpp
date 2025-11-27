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
//= -- engine.addPoint(float x, float y, sf::Color color) - добавление точки цвета color		   =
//= -- engine.addLine({float x1, float y1},{float x2, float x2}, sf::Color color) - добавление     =
//=    линии цвета color																		   =
//= -- engine.addPolygon({float x1, float y1}, ..., {float xn, float yn}, sf::Color color) -	   =
//=    добавление полигона цвета color															   =
//= -- vector<Point> engine.getPoints() - возвращение копии вектора точек						   =
//= -- vector<Line> engine.getLines() - возвращение копии вектора линий							   =
//= -- vector<Polygon> engine.getPolygons() - возвращение копии вектора полигонов				   =
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
	testFunct(engine);
	
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