#pragma once

#include <memory>
#include <string>


// ‘орвард-деклараци€, чтобы не включать SFML в публичный заголовок
namespace sf { class RenderWindow; }

namespace RendUI {
	class Renderer {
	public:
		Renderer(int weidth, int height, const std::string& title);
		~Renderer(); // объ€вл€ем, но определим в .cpp
		void clear();
		void display();
		bool isOpen() const;
		// возвращаем указатель, чтобы не копировать объект и не экспортировать определение типа
		sf::RenderWindow* getWindow();

	private:
		// используем пользовательский тип делитера (function pointer), чтобы не инстанцировать std::default_delete<sf::RenderWindow>
		// в заголовке (default_delete требует полного типа и вызывает static_assert)
		std::unique_ptr<sf::RenderWindow> window;
	};
}