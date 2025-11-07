// Testing.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include "Engine.h"


using namespace RendUI;

int main()
{
	Engine engine(800, 600, "RendUI Engine Test");
	engine.run();
}
