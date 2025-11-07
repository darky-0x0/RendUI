#include "pch.h"    // PCH должен подключатьс€ первым в .cpp
#include "Renderer.h"
#include <SFML/Graphics.hpp>

using namespace RendUI;

// ‘ункци€-делитер определена в .cpp Ч здесь sf::RenderWindow уже полный тип
static void DeleteRenderWindow(sf::RenderWindow* p) {
}

Renderer::Renderer(int weidth, int height, const std::string& title)
	: window(new sf::RenderWindow(sf::VideoMode({ static_cast<unsigned int>(weidth), static_cast<unsigned int>(height) }), title)) {
}

RendUI::Renderer::~Renderer() = default;


void Renderer::clear() {
	if (window) window->clear();
}

void Renderer::display() {
	if (window) window->display();
}

bool Renderer::isOpen() const {
	return window && window->isOpen();
}

sf::RenderWindow* Renderer::getWindow() {
	return window.get();
}
