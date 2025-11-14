#include "pch.h"
#include "framework.h"
#include <Windows.h>
#include <commdlg.h>
#include <fstream>
#include "nlohmann/json.hpp"


// --------------------------------------------
#include "Engine.h"

using namespace RendUI;
using json = nlohmann::json;


std::wstring openFileDialog(bool saveMode);


Engine::Engine(int width, int height, const std::string& title)
	: leftField(0, { 200.f, 500.f }), rightField(1, { 200.f, 500.f }), renderer(width, height, title), coordSystem(50.f), viewState(width, height), UIViewState(width, height), running(true) {


	// Указываем примитивам поле для отображения
	primitives.addElementList(&leftField);

	// Создаём точку-превью
	previewPoint.setRadius(4.f);
	previewPoint.setOrigin({ 4.f, 4.f }); // центрировать
	previewPoint.setFillColor(sf::Color(255, 100, 100, 180));

	// Подгружаем иконку приложения
	auto image = sf::Image{};
	if (!image.loadFromFile("sources/icons/app_icon.png")) {
		std::cout << "Не удалось загрузить иконку приложения.";
		exit(1);
	}
	renderer.getWindow().setIcon(image.getSize(), image.getPixelsPtr());

	// Устанавливаем шаг сетки в менеджер примитивов
	float step = coordSystem.getStep();
	renderer.setStep(step);

	// Добавление инструментов
	toolbar.addTool(RendUI::ToolType::Point, "sources/icons/draw_point.png");
	toolbar.addTool(RendUI::ToolType::Line, "sources/icons/draw_line.png");
	toolbar.addTool(RendUI::ToolType::Polygon, "sources/icons/draw_polygon.png");
	toolbar.addTool(RendUI::ToolType::Delete, "sources/icons/delete_primitive.png");
	toolbar.addTool(RendUI::ToolType::Clear, "sources/icons/delete_all.png");

	fontMain.openFromFile("sources/fonts/LeticeaBumsteadCyrillic.otf"); // Загрузка основного шрифта

	saveButton = std::make_unique<IconButton>(
		"sources/icons/export.png",
		sf::Vector2f(width - 100.f, 10.f),
		[this]() {
			savePrimitivesToJson();
			showNotification("Данные сохранены в data.json");
		});

	loadButton = std::make_unique<IconButton>(
		"sources/icons/import.png",
		sf::Vector2f(width - 50.f, 10.f),
		[this]() {
			loadPrimitivesFromJson();
			showNotification("Данные загружены из data.json");
		});
}



void Engine::run() {

	while (running && renderer.isOpen()) {

		// Первичная инициализация элементов
		

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
			// Обновление уведомлений
			float dt = deltaClock.restart().asSeconds();
			notifications.update(dt);

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
					
					// Координаты в мировых координатах
					sf::Vector2f worldPos = renderer.getWindow().mapPixelToCoords(
						{ pressed->position.x, pressed->position.y },
						viewState.getView()
					);

					// Проверяем, не кликнули ли по интерфейсу
					if (!(toolbar.isMouseOver(renderer.getWindow(), UIViewState.getView()) || leftField.isMouseOver(renderer.getWindow(), UIViewState.getView()) || rightField.isMouseOver(renderer.getWindow(), UIViewState.getView()) || saveButton->isMouseOver(renderer.getWindow(), UIViewState.getView()) || loadButton->isMouseOver(renderer.getWindow(), UIViewState.getView()))) {
	
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
			renderer.getWindow().setView(UIViewState.getView());
			leftField.handleEvent(event, renderer.getWindow(), UIViewState.getView());
			rightField.handleEvent(event, renderer.getWindow(), UIViewState.getView());
			sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(renderer.getWindow());
			saveButton->handleEvent(event, mousePos);
			loadButton->handleEvent(event, mousePos);
			renderer.getWindow().setView(viewState.getView());
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
		leftField.draw(renderer.getWindow(), UIViewState.getView());
		// Рисуем правую панель
		rightField.draw(renderer.getWindow(), UIViewState.getView());
		// Рисуем уведомления
		notifications.draw(renderer.getWindow(), UIViewState.getView());
		// Рисуем кнопки чтения записи
		saveButton->draw(renderer.getWindow(), UIViewState.getView(), 1);
		// Рисуем кнопки чтения записи
		loadButton->draw(renderer.getWindow(), UIViewState.getView(), 2);
		// Восстанавливаем вид сцены
		renderer.getWindow().setView(viewState.getView());

		//---------------------------------------------------------------------------------------------------------------------------------------------


		renderer.display();
	}
}



void Engine::addPoint(float x, float y) { primitives.addPoint(x, y); }
void Engine::addLine(Point a, Point b) { primitives.addLine(a, b); }
void Engine::addPolygon(const std::vector<Point>& vertices) { primitives.addPolygon(vertices); }


void RendUI::Engine::addTask(const std::string& msg, std::function<void()> funct) {
	rightField.addElement<TextButtonElement>(
		msg,
		rightField.getSize().x,   // ширина поля
		fontMain,
		funct
	);
}

void RendUI::Engine::savePrimitivesToJson() {
	std::wstring filePath = openFileDialog(true);
	if (filePath.empty()) return;

	json j;

	// ===== POINTS =====
	auto pts = getPoints();
	for (auto& p : pts)
		j["points"].push_back({ {"x", p.x}, {"y", p.y} });

	// ===== LINES =====
	auto lines = getLines();
	for (auto& l : lines)
	{
		j["lines"].push_back({
			{"a", { {"x", l.a.x}, {"y", l.a.y} }},
			{"b", { {"x", l.b.x}, {"y", l.b.y} }}
			});
	}

	// ===== POLYGONS =====
	auto polys = getPolygons();
	for (auto& poly : polys)
	{
		json vertArr = json::array();
		for (auto& v : poly.vertices)
			vertArr.push_back({ {"x", v.a.x}, {"y", v.a.x} });

		j["polygons"].push_back({ {"vertices", vertArr} });
	}

	std::ofstream file(filePath);
	file << j.dump(4);
	file.close();

}

void RendUI::Engine::loadPrimitivesFromJson() {
	std::wstring filePath = openFileDialog(false);
	if (filePath.empty()) return;

	std::ifstream file(filePath);
	if (!file.is_open()) return;

	json j;
	file >> j;
	file.close();

	deleteAllPrimitives();

	// ===== POINTS =====
	if (j.contains("points"))
	{
		for (auto& p : j["points"])
			addPoint(p["x"], p["y"]);
	}

	// ===== LINES =====
	if (j.contains("lines"))
	{
		for (auto& l : j["lines"])
		{
			Point a{ l["a"]["x"], l["a"]["y"] };
			Point b{ l["b"]["x"], l["b"]["y"] };
			addLine(a, b);
		}
	}

	// ===== POLYGONS =====
	if (j.contains("polygons"))
	{
		for (auto& poly : j["polygons"])
		{
			std::vector<Point> verts;
			for (auto& v : poly["vertices"])
				verts.push_back({ v["x"], v["y"] });

			addPolygon(verts);
		}
	}
}

void Engine::handleLineTool(float x, float y) {
	if (!drawingInProgress) {
		startLinePoint = { x, y };
		drawingInProgress = true;
		tempPrimitives.addPoint(startLinePoint.x, startLinePoint.y);
	}
	else {
		addLine({ startLinePoint.x, startLinePoint.y}, { x, y });
		drawingInProgress = false;
		tempPrimitives.clearAll();
	}
}

void Engine::handlePolygonTool(float x, float y) {
	polygonPoints.push_back({ x, y });

	if(!drawingInProgress) {
		tempPrimitives.addPoint(x, y);
		drawingInProgress = true;
	}
	else if (drawingInProgress) {
		tempPrimitives.addLine({ polygonPoints[polygonPoints.size() - 2].x, polygonPoints[polygonPoints.size() - 2].y }, { polygonPoints[polygonPoints.size() - 1].x, polygonPoints[polygonPoints.size() - 1].y });
	}

	if (polygonPoints.size() > 2 && (polygonPoints[polygonPoints.size()-1].x == polygonPoints[0].x && polygonPoints[polygonPoints.size() - 1].y == polygonPoints[0].y)) {
		addPolygon(polygonPoints);
		polygonPoints.clear();
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
	polygonPoints.clear();
	leftField.removeAllElements();
}

void Engine::showNotification(const std::string& msg) {
	notifications.show(msg, renderer.getWindow());
}



std::wstring openFileDialog(bool saveMode)
{
	// Сохранить текущее рабочее место
	wchar_t oldDir[MAX_PATH];
	GetCurrentDirectoryW(MAX_PATH, oldDir);

	OPENFILENAMEW ofn;
	wchar_t fileName[MAX_PATH] = L"";
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFilter = L"JSON Files\0*.json\0All Files\0*.*\0";
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST;
	if (!saveMode)
		ofn.Flags |= OFN_FILEMUSTEXIST;

	ofn.lpstrDefExt = L"json";

	BOOL result = saveMode ?
		GetSaveFileNameW(&ofn) :
		GetOpenFileNameW(&ofn);

	// ВОССТАНОВИТЬ ПУТЬ ОБРАТНО
	SetCurrentDirectoryW(oldDir);

	if (result)
		return std::wstring(fileName);

	return L"";
}
