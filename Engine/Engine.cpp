#include "pch.h"
#include "framework.h"

// --------------------------------------------
#include "Engine.h"

using namespace RendUI;


Engine::Engine(int width, int height, const std::string& title) : renderer(width, height, title), running(true) {}


void Engine::run() {

	while (running && renderer.isOpen()) {
		// Обработка событий
		auto& window = renderer.getWindow();
		while (auto eventOpt = window.pollEvent()) {
			const sf::Event event = *eventOpt;

			// Закрытие окна
			if (event.is<sf::Event::Closed>()) { input.process(window);	}

			// Ресайз окна
			if (const auto* resized = event.getIf<sf::Event::Resized>()) {
				// Обновляем view в Renderer
				renderer.updateView(resized->size.x, resized->size.y);
			}

			// Закрытие окна по нажатию Escape
			if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
					input.process(window);
				}
			}

		}

		if (input.isClosed()) { running = false; }


		// Очищаем экран перед новой отрисовкой
		renderer.clear();

		// Указываем рендер, который будет использоваться для отрисовки сетки
		grid.draw(renderer);

		renderer.update(primitives);

		renderer.display();
	}
}



void Engine::addPoint(float x, float y) { primitives.addPoint(x, y); }
void Engine::addLine(Point a, Point b) { primitives.addLine(a, b); }
void Engine::addPolygon(const std::vector<Point>& vertices) { primitives.addPolygon(vertices); }