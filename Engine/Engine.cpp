#include "pch.h"
#include "framework.h"

// --------------------------------------------
#include "Engine.h"

using namespace RendUI;


Engine::Engine(int width, int height, const std::string& title) 
	: leftField({ 10.f, 10.f }, { 200.f, 500.f }), renderer(width, height, title), coordSystem(50.f), viewState(width, height), UIViewState(width, height), running(true) {

	// Создаём точку-превью
	previewPoint.setRadius(4.f);
	previewPoint.setOrigin({ 4.f, 4.f }); // центрировать
	previewPoint.setFillColor(sf::Color(255, 100, 100, 180));

	// Подгружаем иконку приложения
	auto image = sf::Image{};
	if (!image.loadFromFile("icons/app_icon.png")) {
				std::cout << "Не удалось загрузить иконку приложения.";
				exit(1);
	}
	renderer.getWindow().setIcon(image.getSize(), image.getPixelsPtr());
	
	// Устанавливаем шаг сетки в менеджер примитивов
	float step = coordSystem.getStep();
	renderer.setStep(step);

	// Добавление инструментов
	toolbar.addTool(RendUI::ToolType::Point, "icons/draw_point.png");
	toolbar.addTool(RendUI::ToolType::Line, "icons/draw_line.png");
	toolbar.addTool(RendUI::ToolType::Polygon, "icons/draw_polygon.png");
	toolbar.addTool(RendUI::ToolType::Delete, "icons/delete_primitive.png");
	toolbar.addTool(RendUI::ToolType::Clear, "icons/delete_all.png");

	// Добавление элементов в левое поле
	leftField.addItem({
		"icons/point.png",
		40.f,
		false,
		[]() { std::cout << "Выбран Point\n"; },
		[]() { std::cout << "Удалён Point\n"; }
	});

	leftField.addItem({
		"icons/line.png",
		40.f,
		false,
		[]() { std::cout << "Выбран Line\n"; },
		[]() { std::cout << "Удалён Line\n"; }
	});

	leftField.addItem({
		"icons/polygon.png",
		40.f,
		false,
		[]() { std::cout << "Выбран Polygon\n"; },
		[]() { std::cout << "Удалён Polygon\n"; }
	});

	leftField.addItem({
	"icons/polygon.png",
	40.f,
	false,
	[]() { std::cout << "Выбран Polygon\n"; },
	[]() { std::cout << "Удалён Polygon\n"; }
		});
	leftField.addItem({
	"icons/polygon.png",
	40.f,
	false,
	[]() { std::cout << "Выбран Polygon\n"; },
	[]() { std::cout << "Удалён Polygon\n"; }
		});
	leftField.addItem({
	"icons/polygon.png",
	40.f,
	false,
	[]() { std::cout << "Выбран Polygon\n"; },
	[]() { std::cout << "Удалён Polygon\n"; }
		});
	leftField.addItem({
	"icons/polygon.png",
	40.f,
	false,
	[]() { std::cout << "Выбран Polygon\n"; },
	[]() { std::cout << "Удалён Polygon\n"; }
		});
	leftField.addItem({
"icons/polygon.png",
40.f,
false,
[]() { std::cout << "Выбран Polygon\n"; },
[]() { std::cout << "Удалён Polygon\n"; }
		});
	leftField.addItem({
"icons/polygon.png",
40.f,
false,
[]() { std::cout << "Выбран Polygon\n"; },
[]() { std::cout << "Удалён Polygon\n"; }
		});
	leftField.addItem({
"icons/polygon.png",
40.f,
false,
[]() { std::cout << "Выбран Polygon\n"; },
[]() { std::cout << "Удалён Polygon\n"; }
		});
	leftField.addItem({
"icons/polygon.png",
40.f,
false,
[]() { std::cout << "Выбран Polygon\n"; },
[]() { std::cout << "Удалён Polygon\n"; }
		});
	leftField.addItem({
"icons/polygon.png",
40.f,
false,
[]() { std::cout << "Выбран Polygon\n"; },
[]() { std::cout << "Удалён Polygon\n"; }
		});
	leftField.addItem({
"icons/polygon.png",
40.f,
false,
[]() { std::cout << "Выбран Polygon\n"; },
[]() { std::cout << "Удалён Polygon\n"; }
		});
	leftField.addItem({
"icons/polygon.png",
40.f,
false,
[]() { std::cout << "Выбран Polygon\n"; },
[]() { std::cout << "Удалён Polygon\n"; }
		});
	leftField.addItem({
"icons/polygon.png",
40.f,
false,
[]() { std::cout << "Выбран Polygon\n"; },
[]() { std::cout << "Удалён Polygon\n"; }
		});
	leftField.addItem({
"icons/polygon.png",
40.f,
false,
[]() { std::cout << "Выбран Polygon\n"; },
[]() { std::cout << "Удалён Polygon\n"; }
		});
	leftField.addItem({
"icons/polygon.png",
40.f,
false,
[]() { std::cout << "Выбран Polygon\n"; },
[]() { std::cout << "Удалён Polygon\n"; }
		});
	leftField.addItem({
"icons/polygon.png",
40.f,
false,
[]() { std::cout << "Выбран Polygon\n"; },
[]() { std::cout << "Удалён Polygon\n"; }
		});
	leftField.addItem({
"icons/polygon.png",
40.f,
false,
[]() { std::cout << "Выбран Polygon\n"; },
[]() { std::cout << "Удалён Polygon\n"; }
		});
	leftField.addItem({
"icons/polygon.png",
40.f,
false,
[]() { std::cout << "Выбран Polygon\n"; },
[]() { std::cout << "Удалён Polygon\n"; }
		});
	leftField.addItem({
"icons/polygon.png",
40.f,
false,
[]() { std::cout << "Выбран Polygon\n"; },
[]() { std::cout << "Удалён Polygon\n"; }
		});
	leftField.addItem({
"icons/polygon.png",
40.f,
false,
[]() { std::cout << "Выбран Polygon\n"; },
[]() { std::cout << "Удалён Polygon\n"; }
		});
	leftField.addItem({
"icons/polygon.png",
40.f,
false,
[]() { std::cout << "Выбран Polygon\n"; },
[]() { std::cout << "Удалён Polygon\n"; }
		});
	leftField.addItem({
"icons/polygon.png",
40.f,
false,
[]() { std::cout << "Выбран Polygon\n"; },
[]() { std::cout << "Удалён Polygon\n"; }
		});
	leftField.addItem({
"icons/polygon.png",
40.f,
false,
[]() { std::cout << "Выбран Polygon\n"; },
[]() { std::cout << "Удалён Polygon\n"; }
		});

}


void Engine::run() {

	while (running && renderer.isOpen()) {

		// Сохраняем стандартный вид окна для UI
		UIViewState.setView((float)renderer.getWindow().getSize().x, (float)renderer.getWindow().getSize().y);

		// Получаем текущий выбранный инструмент
		auto newTool = toolbar.getSelectedTool();
		if(newTool != currentTool) {
			currentTool = newTool;
			// Сбрасываем состояние рисования, если инструмент изменился
			drawingInProgress = false;
			tempPrimitives.clearAll();
		}

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
				// Фикс UI при ресайзе
				UIViewState.resizeUI(renderer.getWindow());
			}

			// Следование превью-точки за мышью
			if (const auto* moved = event.getIf<sf::Event::MouseMoved>()) {
				if (currentTool == ToolType::Point || currentTool == ToolType::Line || currentTool == ToolType::Polygon || currentTool == ToolType::Delete) {
					sf::Vector2f worldPos = renderer.getWindow().mapPixelToCoords(
						{ moved->position.x, moved->position.y },
						viewState.getView()
					);

					float step = coordSystem.getStep();

					// Проверяем, зажат ли Shift
					bool shiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) ||
						sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift);

					if (!shiftPressed) {
						// Привязка к сетке
						worldPos.x = std::round(worldPos.x / step) * step;
						worldPos.y = std::round(worldPos.y / step) * step;
					}

					previewPoint.setPosition(worldPos);
					showPreview = true;
				}
				else {
					showPreview = false;
				}
			}

			// Нажатие кнопок мыши
			if (const auto* pressed = event.getIf<sf::Event::MouseButtonPressed>()) {

				// ПКМ — возможно перемещение камеры
				if (pressed->button == sf::Mouse::Button::Right) {
					rightMousePressed = true;
					lastMousePos = sf::Vector2f((float)pressed->position.x, (float)pressed->position.y);
				}

				// ЛКМ — действие инструмента
				else if (pressed->button == sf::Mouse::Button::Left) {

					// Проверяем, не кликнули ли по интерфейсу
					if (!(toolbar.isMouseOver(renderer.getWindow(), UIViewState.getView()) || leftField.isMouseOver(renderer.getWindow(), UIViewState.getView()))) {

						// Координаты в мировых координатах
						sf::Vector2f worldPos = renderer.getWindow().mapPixelToCoords(
							{ pressed->position.x, pressed->position.y },
							viewState.getView()
						);
	
						// Старая обработка координат
						//float x_old = worldPos.x / coordSystem.getStep();
						//float y_old = worldPos.y / coordSystem.getStep();

						// Новая обработка координат с учётом привязки к сетке
						float x = previewPoint.getPosition().x / coordSystem.getStep();
						float y = previewPoint.getPosition().y / coordSystem.getStep();

						//std::cout << "Клик в мировых координатах: (" << x_old << ", " << y_old << ") " << "  (" << x << ", " << y << ")\n";

						// Вызываем соответствующее действие
						switch (currentTool) {
						case ToolType::Point:
							addPoint(x, y);
							break;

						case ToolType::Line:
							handleLineTool(x, y);
							break;

						case ToolType::Polygon:
							handlePolygonTool(x, y);
							break;

						case ToolType::Delete:
							handleDeleteTool(x, y);
							break;

						}
					}
					else {
						if (currentTool == ToolType::Clear) {
							deleteAllPrimitives();
						}
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
			// Переключаемся на «экранный» вид
			renderer.getWindow().setView(UIViewState.getView());
			// Считываем нажатие на интерфейс
			toolbar.handleEvent(event, renderer.getWindow());
			// Считываем нажатие на левую панель
			leftField.handleEvent(event, renderer.getWindow(), UIViewState.getView());
			// Восстанавливаем вид сцены
			renderer.getWindow().setView(viewState.getView());
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

		// Рисуем координатную сетку
		coordSystem.draw(renderer.getWindow(), viewState.getView());

		// Рисуем примитивы
		renderer.update(primitives);
		// Рисуем временные примитивы (например, рисуемую линию)
		renderer.update(tempPrimitives);

		// Рисуем превью-точку, если нужно
		if (showPreview)
			renderer.getWindow().draw(previewPoint);

		//---------------------------------------------------------- Рисование поверх экрана ----------------------------------------------------------
		// Переключаемся на «экранный» вид
		renderer.getWindow().setView(UIViewState.getView());
		// Рисуем Toolbar
		toolbar.draw(renderer.getWindow());
		// Рисуем левую панель
		leftField.draw(renderer.getWindow(), UIViewState);
		// Восстанавливаем вид сцены
		renderer.getWindow().setView(viewState.getView());

		//---------------------------------------------------------------------------------------------------------------------------------------------


		renderer.display();
	}
}



void Engine::addPoint(float x, float y) { primitives.addPoint(x, y); }
void Engine::addLine(Point a, Point b) { primitives.addLine(a, b); }
void Engine::addPolygon(const std::vector<Point>& vertices) { primitives.addPolygon(vertices); }


void Engine::handleLineTool(float x, float y) {
	static sf::Vector2f startPoint;

	if (!drawingInProgress) {
		startPoint = { x, y };
		drawingInProgress = true;
		tempPrimitives.addPoint(startPoint.x, startPoint.y);
	}
	else {
		addLine({startPoint.x, startPoint.y}, { x, y });
		drawingInProgress = false;
		tempPrimitives.clearAll();
	}
}

void Engine::handlePolygonTool(float x, float y) {
	static std::vector<Point> points;
	static sf::Vector2f startPoint;
	points.push_back({ x, y });

	if(!drawingInProgress) {
		startPoint = { x, y };
		tempPrimitives.addPoint(startPoint.x, startPoint.y);
		drawingInProgress = true;
	}
	else if (drawingInProgress) {
		tempPrimitives.addLine({ points[points.size() - 2].x, points[points.size() - 2].y }, { points[points.size() - 1].x, points[points.size() - 1].y });
	}

	if (points.size() > 2 && (points[points.size()-1].x == points[0].x && points[points.size() - 1].y == points[0].y)) {
		addPolygon(points);
		points.clear();
		tempPrimitives.clearAll();
		drawingInProgress = false;
	}
}

void Engine::handleDeleteTool(float x, float y) {
	primitives.deletePrimitiveAt(x, y);
}

void Engine::deleteAllPrimitives() {
	drawingInProgress = false;
	primitives.clearAll();
	tempPrimitives.clearAll();
}
