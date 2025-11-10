// Testing.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.


#include <iostream>
#include "Engine.h"


using namespace RendUI;

int main()
{
	setlocale(0, "");
	Engine engine(800, 600, "RendUI Engine Test");
	engine.addPoint(2.f, 1.f);
	engine.addLine({ 3.f, 3.f }, { 6.f, 6.f });
	engine.addPolygon({ {8.f, 8.f}, {10.f, 8.f}, {11.f, 10.f}, {9.f, 11.f} });
	//engine.deleteAllPrimitives();
	engine.run();
	return 0;
}
