#include "pch.h"
#include "Input.h"


using namespace RendUI;

void Input::process(sf::RenderWindow& window) {
	closed = true;
	window.close();
}
