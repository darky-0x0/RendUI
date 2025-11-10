// Testing.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.


#include <iostream>
#include "Engine.h"


using namespace RendUI;

int main()
{
	Engine engine(800, 600, "RendUI Engine Test");
	engine.addPoint(100.f, 100.f);
	engine.addLine({ 150.f, 150.f }, { 300.f, 300.f });
	engine.addPolygon({ {400.f, 400.f}, {500.f, 400.f}, {550.f, 500.f}, {450.f, 550.f} });
	engine.run();
	return 0;
}
