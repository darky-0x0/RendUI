#pragma once

#include "Primitive.hpp"
#include "PrimitivesManager.h"


namespace RendUI {
	class Renderer {
	public:
		Renderer(int weidth, int height, const std::string& title);
		void clear();
		void display();
		bool isOpen() const;

		// update читает менеджер, поэтому принимаем const&
		void update(const PrimitivesManager& primitives);

		// возвращаем указатель, чтобы не копировать объект и не экспортировать определение типа
		sf::RenderWindow& getWindow();
		void setStep(float s) { step = s; }

		// принимаем const& чтобы избежать копирования и предупреждений о преобразовании
		void drawPoint(const Point& p, const float radius = 6.0f);
		void drawLine(const Line& l);
		void drawPolygon(const Polygon& poly);

		//void drawGrid(float step, sf::Color gridColor);

	private:
		sf::RenderWindow window;
		float windowWidth;
		float windowHeight;
		float step = 1;
	};
}