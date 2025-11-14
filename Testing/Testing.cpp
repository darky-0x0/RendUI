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
	engine.addLine({ 3.f, 3.f }, { 6.f, 6.f });
	engine.addPolygon({ {8.f, 8.f}, {10.f, 8.f}, {11.f, 10.f}, {9.f, 11.f} });
	engine.showNotification("Добро пожаловать в программу!");
	testFunct(engine);
	//engine.deleteAllPrimitives();
	
	
	engine.run();
	return 0;
}


void testFunct(Engine& engine) {
	engine.addTask("Hello мир2!", [&engine] {
		std::cout << "Привет мир!";
		engine.showNotification("Лан л");
		std::vector<Point> points = engine.getPoints();
		std::cout << points[0].x << ":" << points[0].y;
	});
}