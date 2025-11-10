#include "pch.h"
#include "framework.h"

// --------------------------------------------
#include "Engine.h"

using namespace RendUI;


Engine::Engine(int width, int height, const std::string& title) : renderer(width, height, title), coordSystem(50.f), viewState(width, height), running(true) {
	// Устанавливаем шаг сетки в менеджер примитивов
	float step = coordSystem.getStep();
	renderer.setStep(step);
}


void Engine::run() {

	while (running && renderer.isOpen()) {


		// ----------------------------------------------------- ИВЕНТЫ -----------------------------------------------------
		// 
		//
		// ------------------------------------------------------------------------------------------------------------------
		while (auto eventOpt = renderer.getWindow().pollEvent()) {
			const sf::Event event = *eventOpt;

			// Закрытие окна
			if (event.is<sf::Event::Closed>()) { input.process(renderer.getWindow());	}

			// Ресайз окна
			if (const auto* resized = event.getIf<sf::Event::Resized>()) {
				// Обновляем view в Renderer
				//renderer.updateView(resized->size.x, resized->size.y);
				viewState.resize(renderer.getWindow());
			}

			if (const auto* pressed = event.getIf<sf::Event::MouseButtonPressed>()) {
				// Нажатие ПКМ
				if (pressed->button == sf::Mouse::Button::Right) {
					rightMousePressed = true;
					lastMousePos = sf::Vector2f((float)pressed->position.x, (float)pressed->position.y);
				}
				// Левый клик — добавление точки
				else if (const auto* pressed = event.getIf<sf::Event::MouseButtonPressed>()) {
					if (pressed->button == sf::Mouse::Button::Left) {
						// Преобразуем экранные координаты мыши в координаты мира
						sf::Vector2f worldPos = renderer.getWindow().mapPixelToCoords({ pressed->position.x, pressed->position.y }, viewState.getView());

						// Делим на шаг сетки, если используем масштабирование координат
						float x = worldPos.x / coordSystem.getStep();
						float y = worldPos.y / coordSystem.getStep();

						addPoint(x, y); // добавляем точку
					}
				}
			}

			// Отпускание ПКМ
			if (const auto* released = event.getIf<sf::Event::MouseButtonReleased>()) {
				if (released->button == sf::Mouse::Button::Right) {
					rightMousePressed = false;
				}
			}

			// Движение мыши
			if (const auto* moved = event.getIf<sf::Event::MouseMoved>()) {
				if (rightMousePressed) {
					float currentZoom = viewState.getZoom();
					sf::Vector2f currentPos((float)moved->position.x, (float)moved->position.y);
					sf::Vector2f delta = lastMousePos - currentPos;
					viewState.move(delta.x * currentZoom, -delta.y * currentZoom);
					lastMousePos = currentPos;
				}
			}

			// Колёсико мыши
			if (const auto* wheel = event.getIf<sf::Event::MouseWheelScrolled>()) {
				if (wheel->delta > 0) {
					viewState.zoom(1.0f / zoomFactor);
				}
				else if (wheel->delta < 0) {
					viewState.zoom(zoomFactor);
				}
			}

			// Обработка нажатий клавиш
			if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
				switch (keyPressed->scancode) {
				// Закрытие окна по нажатию Escape
				case sf::Keyboard::Scancode::Escape:
					input.process(renderer.getWindow());
					break;
				case sf::Keyboard::Scancode::R:
					viewState.resetOffset();
					viewState.resize(renderer.getWindow());
					break;
				}

			}

		}

		// ----------------------------------------------- КОНЕЦ ИВЕНТОВ ------------------------------------------------
		// 
		//
		// --------------------------------------------------------------------------------------------------------------


		if (input.isClosed()) { running = false; }


		// Очищаем экран перед новой отрисовкой
		renderer.clear();


		// Применяем текущее состояние вида
		viewState.applyTo(renderer.getWindow());

		//// Указываем рендер, который будет использоваться для отрисовки сетки
		//grid.draw(renderer);

		// Рисуем координатную сетку
		coordSystem.draw(renderer.getWindow(), viewState.getView());

		renderer.update(primitives);

		renderer.display();
	}
}



void Engine::addPoint(float x, float y) { primitives.addPoint(x, y); }
void Engine::addLine(Point a, Point b) { primitives.addLine(a, b); }
void Engine::addPolygon(const std::vector<Point>& vertices) { primitives.addPolygon(vertices); }

void Engine::deleteAllPrimitives() {
	primitives.clearAll();
}
