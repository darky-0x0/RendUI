#pragma once
#include "Renderer.h"

namespace RendUI {
	class Grid
	{
	public:
		Grid(float step = 50.f);
		void draw(Renderer& renderer);
	private:
		float step;
	};
}

