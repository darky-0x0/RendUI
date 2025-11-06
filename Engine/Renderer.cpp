#include "pch.h"
#include "Renderer.h"

using namespace RendUI;



Renderer::Renderer(int weidth, int height, const string& title) : window(sf::VideoMode({ weidth, height }), title) {}

void Renderer::clear() {
	
}

void Renderer::display() {

}

bool Renderer::isOpen() const {
	return false;
}

sf::RenderWindow RendUI::Renderer::getWindow() {
	return sf::RenderWindow();
}
