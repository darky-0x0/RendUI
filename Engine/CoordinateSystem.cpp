#include "pch.h"
#include "CoordinateSystem.h"




using namespace RendUI;

CoordinateSystem::CoordinateSystem(float step) : step(step), gridColor(60, 60, 60), axisColor(200, 50, 50) {
	if (!font.openFromFile("sources/fonts/clash_text_vi_th.ttf")) { // путь к шрифту
		std::cerr << "Не удалось загрузить шрифт!" << std::endl;
		exit(1);
	}
}


void CoordinateSystem::draw(sf::RenderWindow& window, const sf::View& view) {

	// Получаем границы видимой области
	sf::Vector2 center = view.getCenter();
	sf::Vector2 size = view.getSize();

	float left = center.x - size.x / 2.f;
	float right = center.x + size.x / 2.f;
	float bottom = center.y - size.y / 2.f;
	float top = center.y + size.y / 2.f;

	sf::VertexArray lines(sf::PrimitiveType::Lines);

	// Рисуем вертикальные линии сетки
	float startX = std::floor(left / step) * step;
	for (float x = startX; x <= right; x += step) {
		lines.append(sf::Vertex{ {x, top}, gridColor });
		lines.append(sf::Vertex{ {x, bottom}, gridColor });
	}

	// Рисуем горизонтальные линии сетки
	float startY = std::floor(top / step) * step;
	for (float y = startY; y <= bottom; y += step) {
		lines.append(sf::Vertex{ {left, y}, gridColor });
		lines.append(sf::Vertex{ {right, y}, gridColor });
	}

	// Оси
	lines.append(sf::Vertex{ {0.f, top}, axisColor });
	lines.append(sf::Vertex{ {0.f, bottom}, axisColor });
	lines.append(sf::Vertex{ {left, 0.f}, axisColor });
	lines.append(sf::Vertex{ {right, 0.f}, axisColor });

	window.draw(lines);



	// Подписи чисел
	if (font.getInfo().family != "") {
		for (float x = startX; x <= right; x += step) {
			if (std::abs(x) < 1e-3) continue; // пропускаем ось
			sf::Text text(font);
			text.setString(std::to_string((int)(x / step)));
			text.setCharacterSize(12);
			text.setScale({ 1.f, -1.f });
			text.setFillColor(sf::Color(120, 120, 120));
			text.setPosition({ x + 2, 2 });
			window.draw(text);
		}

		for (float y = startY; y <= bottom; y += step) {
			if (std::abs(y) < 1e-3) continue;
			sf::Text text(font);
			text.setString(std::to_string((int)(y / step)));
			text.setCharacterSize(12);
			text.setScale({ 1.f, -1.f });
			text.setFillColor(sf::Color(120, 120, 120));
			text.setPosition({ 2, y + 2 });
			window.draw(text);
		}
	}

}
