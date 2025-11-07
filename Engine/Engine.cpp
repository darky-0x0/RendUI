#include "pch.h"
#include "framework.h"

// --------------------------------------------
#include "Engine.h"

using namespace RendUI;


Engine::Engine(int width, int height, const std::string& title) : renderer(width, height, title), running(true) {}


void Engine::run() {
	while (running && renderer.isOpen()) {
		
	}
}