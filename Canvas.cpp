// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Canvas.h"
#include <iostream>

Canvas::Canvas(const sf::Vector2f& position, const sf::Vector2f& size, sf::RenderWindowt& window) :
	_size(size), _position(position), _thickness(2.f), _mode(Tool::Mode::Pencil), _tools(window) {

	_shape.setSize(size);
	_shape.setPosition(position);
	_shape.setFillColor(sf::Color::White);
	_shape.setOutlineColor(sf::Color::Black);
	_shape.setOutlineThickness(2.f);
}

bool Canvas::handleEvent(const sf::Event& event) {
	if (event.type == event.MouseButtonPressed) {
		if (sf::FloatRect(_position.x, _position.y, _size.x, _size.y).contains({ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) })) {
			_tools[_mode].onPress(event);
		}
	} else if (event.type == event.MouseButtonReleased) {
		if (sf::FloatRect(_position.x, _position.y, _size.x, _size.y).contains({ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) })) {
			_tools[_mode].onRelease(event);
		}

	} else if (event.type == event.MouseMoved) {
		if (sf::FloatRect(_position.x, _position.y, _size.x, _size.y).contains({ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) })) {
			if (_tools[_mode].status == Tool::Status::Dragging) {
				_tools[_mode].onDrag(event);
			} else {
				_tools[_mode].onMove(event);
			}
		} else {
			if (_tools[_mode].status == Tool::Status::Dragging) {
				_tools[_mode].onRelease(event);
			}
			_tools[_mode].onNothing();
		}
	}

	return true;
}


sf::Vector2f Canvas::getSize() const {
	return _size;
}

void Canvas::setColor(const sf::Color& color) {
	_color = color;
}

void Canvas::setThickness(const float thickness) {
	_thickness = thickness;
}

void Canvas::setMode(Tool::Mode mode) {
	_mode = mode;
}

void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_shape, states);
}
//
//void Canvas::initDrawMap() {
//
//	initPencil();
//	initLine();
//	initCircle();
//	initRectangle();
//	initErase();
//}
//
//void Canvas::initPencil() {
//
//	_drawMap.insert(std::pair<Mode, std::unique_ptr<Pencil>>(Mode::Pencil, std::make_unique<Pencil>(std::move(Pencil()))));
//
//	auto& map = _drawMap[Mode::Pencil];
//	map->onPress = [&](const sf::Event & event) mutable {
//		map->setStatus(Status::Dragging);
//		map->last = { static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };
//	};
//
//	map->onRelease = [&](const sf::Event&) mutable {
//		map->setStatus(Status::None);
//	};
//
//	map->onDrag = [&, lines = &_lines](const sf::Event & event) mutable {
//
//		sf::Vector2f newLast{ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };
//
//		ThickLine line(map->last, newLast, _thickness, _color);
//
//		lines->push_back(line);
//
//		map->last = newLast;
//	};
//
//	map->onMove = [](const sf::Event&) {};
//}
//
//void Canvas::initLine() {
//
//	_drawMap.insert(std::pair<Mode, std::unique_ptr<Tool>>(Mode::Line, std::make_unique<Tool>(std::move(Tool()))));
//	auto& map = _drawMap[Mode::Line];
//
//	map->onPress = [&, lines = &_lines](const sf::Event & event) mutable {
//		if (map->last.x < 0.1f && map->last.y < 0.1f) {
//			map->setStatus(Status::Moving);
//
//			sf::Vector2f newLast{ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };
//			map->last = newLast;
//
//			ThickLine line(newLast, newLast, _thickness, _color);
//			lines->push_back(line);
//		} else {
//			map->status = Status::None;
//		}
//	};
//
//	map->onRelease = [&, lines = &_lines](const sf::Event&) mutable {
//		if (map->status == Status::None) {
//			map->last = { 0.f, 0.f };
//		}
//	};
//
//	map->onDrag = [](const sf::Event&) {
//
//	};
//
//	map->onMove = [&, lines = &_lines](const sf::Event & event) mutable {
//		if (map->last.x > 0.1f && map->last.y > 0.1f) {
//			if (!lines->empty()) {
//				lines->back().setEnd({ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) });
//			}
//		}
//	};
//}
//
//void Canvas::initCircle() {
//	_drawMap.insert(std::pair<Mode, std::unique_ptr<Tool>>(Mode::Circle, std::make_unique<Tool>(std::move(Tool()))));
//	auto& map = _drawMap[Mode::Circle];
//
//	map->onPress = [&, circles = &_circles](const sf::Event & event) mutable {
//		if (map->last.x < 0.1f && map->last.y < 0.1f) {
//			map->setStatus(Status::Moving);
//			map->last = { static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };
//
//			sf::CircleShape circle;
//			circle.setPosition(map->last);
//			circle.setRadius(0.f);
//			circle.setOutlineColor(_color);
//			circle.setOutlineThickness(_thickness);
//			circle.setFillColor(sf::Color::Transparent);
//
//			circles->push_back(circle);
//		} else {
//			map->status = Status::None;
//		}
//	};
//
//	map->onRelease = [&, circles = &_circles](const sf::Event&) mutable {
//		if (map->status == Status::None) {
//			map->last = { 0.f, 0.f };
//		}
//	};
//
//	map->onDrag = [](const sf::Event&) {
//
//	};
//
//	map->onMove = [&, circles = &_circles](const sf::Event & event) mutable {
//		if ((map->last.x > 0.1f && map->last.y > 0.1f) && !circles->empty()) {
//
//			auto& last = circles->back();
//
//			auto circleBounds = last.getGlobalBounds();
//			auto canvasBounds = _shape.getGlobalBounds();
//
//			if ((circleBounds.left + circleBounds.width + 5 < canvasBounds.left + canvasBounds.width) &&
//				(circleBounds.top + circleBounds.height + 5 < canvasBounds.top + canvasBounds.height)) {
//				sf::Vector2f newLast{ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };
//				auto diff = newLast - map->last;
//				last.setRadius((std::sqrtf(diff.x * diff.x + diff.y + diff.y)) / 2);
//			} else {
//				last.setRadius(last.getRadius() - 10);
//			}
//		}
//	};
//}
//
//void Canvas::initRectangle() {
//
//	_drawMap.insert(std::pair<Mode, std::unique_ptr<Tool>>(Mode::Rectangle, std::make_unique<Tool>(std::move(Tool()))));
//	auto& map = _drawMap[Mode::Rectangle];
//
//	map->onPress = [&, rects = &_rectangles](const sf::Event & event) mutable {
//		if (map->last.x < 0.1f && map->last.y < 0.1f) {
//			map->setStatus(Status::Moving);
//			map->last = { static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };
//
//			sf::RectangleShape rectangle;
//			rectangle.setPosition(map->last);
//			rectangle.setSize({ 0.f, 0.f });
//			rectangle.setOutlineColor(_color);
//			rectangle.setOutlineThickness(_thickness);
//			rectangle.setFillColor(sf::Color::Transparent);
//
//			rects->push_back(rectangle);
//		} else {
//			map->status = Status::None;
//		}
//	};
//
//	map->onRelease = [&, rects = &_rectangles](const sf::Event&) mutable {
//		if (map->status == Status::None) {
//			map->last = { 0.f, 0.f };
//		}
//	};
//
//	map->onDrag = [](const sf::Event&) {
//
//	};
//
//	map->onMove = [&, rects = &_rectangles](const sf::Event & event) mutable {
//		if ((map->last.x > 0.1f && map->last.y > 0.1f) && !rects->empty()) {
//
//			auto& last = rects->back();
//
//			auto rectangleBounds = last.getGlobalBounds();
//			auto canvasBounds = _shape.getGlobalBounds();
//
//			sf::Vector2f newLast{ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };
//			auto diff = newLast - map->last;
//			last.setSize(diff);
//		}
//	};
//}
//
//void Canvas::initErase() {
//
//	_drawMap.insert(std::pair<Mode, std::unique_ptr<Pencil>>(Mode::Erase, std::make_unique<Pencil>(std::move(Pencil()))));
//
//	auto& map = _drawMap[Mode::Erase];
//	map->onPress = [&, rects = &_rectangles](const sf::Event & event) mutable {
//		map->setStatus(Status::Dragging);
//
//		sf::RectangleShape erase;
//		erase.setOutlineColor(sf::Color::Black);
//		erase.setOutlineThickness(1.f);
//		erase.setFillColor(sf::Color::White);
//		erase.setSize({ _thickness * 4.f, _thickness * 4.f });
//		erase.setOrigin(_thickness / 2.f, _thickness / 2.f);
//		erase.setPosition({ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) });
//		
//		//map->last= { static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };
//		map->last = { static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };
//		rects->push_back(erase);
//	};
//
//	map->onRelease = [&, rects = &_rectangles](const sf::Event&) mutable {
//		if (!rects->empty()) {
//			rects->pop_back();
//		}
//		map->setStatus(Status::None);
//	};
//
//	map->onDrag = [&, rects = &_rectangles, lines = &_lines](const sf::Event & event) mutable {
//
//		if (!rects->empty()) {
//			sf::Vector2f newLast{ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };
//			rects->back().setPosition(newLast);
//		}
//
//		sf::Vector2f newLast{ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };
//
//		auto& erase = rects->back();
//		sf::Vector2f begin = { erase.getPosition().x + erase.getSize().x / 2.f, erase.getPosition().y };
//		sf::Vector2f end = { erase.getPosition().x + erase.getSize().x / 2.f,  erase.getPosition().y + erase.getSize().y};
//
//		ThickLine line(begin, end, erase.getSize().x, sf::Color::White);
//
//		lines->push_back(line);
//
//		map->last = newLast;
//	};
//
//	map->onMove = [](const sf::Event&) {};
//}