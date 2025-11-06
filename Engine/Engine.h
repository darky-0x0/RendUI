#pragma once
#include "Renderer.h"
#include "Input.h"





namespace RendUI {
	class Engine {
	public:
		Engine(int width, int height, const string& title);
		void run();
	private:
		Renderer renderer;
		Input input;
		bool running = false;
	};
}


