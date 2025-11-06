#pragma once


namespace RendUI {
	class Renderer {
	public:
		Renderer(int weidth, int height, const string& title);
		void clear();
		void display();
		bool isOpen() const;
		sf::RenderWindow getWindow();

	private:
		sf::RenderWindow window;
	};
}