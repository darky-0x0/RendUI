#pragma once
#include "Renderer.h"


namespace RendUI {
	class Input {
	public:
		void process(sf::RenderWindow& window);
		bool isClosed() const { return closed; }

	private:
		bool closed = false;
	};
}
