#include "pch.h"
#include "ViewState.h"



using namespace RendUI;

ViewState::ViewState(float firstWidth, float firstHeight) : offset(0, 0), zoomLevel(1.0f), view(sf::FloatRect({ 0,0 }, { firstWidth, firstHeight })) {

	initialCenter = view.getCenter();
	initialSize = view.getSize();

	view.setSize({ initialSize.x, -initialSize.y });
}



void ViewState::move(float offsetX, float offsetY) {
	offset.x += offsetX;
	offset.y += offsetY;
	view.move({ offsetX, offsetY });
}


void ViewState::zoom(float factor) {
	zoomLevel *= factor;
	view.zoom(factor);
}


void RendUI::ViewState::resize(sf::RenderWindow& window) {
	width = (float)window.getSize().x;
	height = (float)window.getSize().y;
	view.setSize({ width * zoomLevel, -height * zoomLevel });
}

void RendUI::ViewState::resetOffset() {
	offset = { 0.f, 0.f };
	zoomLevel = 1.f;

	// Устанавливаем view в исходное состояние
	view.setCenter(initialCenter);   // сохраняется при создании
	view.setSize(initialSize);       // исходный размер окна
}


void ViewState::applyTo(sf::RenderWindow& window) {
	window.setView(view);
}

