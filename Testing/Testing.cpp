// Testing.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.


#include <iostream>
#include "Engine.h"


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