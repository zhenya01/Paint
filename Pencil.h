#pragma once
#include "Tool.h"
#include "ThickLine.h"

namespace Tool {
	class Pencil :
		public Tool {
	public:
		Pencil() : Tool(Mode::Pencil), thickness(2.f), color(sf::Color::Black) {};
		virtual ~Pencil() {};

	public:
		sf::Vector2f last;
		float thickness;
		sf::Color color;
		ThickLine line;
	};

}
