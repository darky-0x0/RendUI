#include "pch.h"
#pragma once


namespace RendUI {
	class Renderer;
	
	struct Point {
		float x, y;
	};
	
	struct Line {
		Point a, b;
	};

	struct Polygon {
		std::vector<Line> vertices;
	};
}