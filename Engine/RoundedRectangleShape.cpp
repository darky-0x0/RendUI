#include "pch.h"
#include "RoundedRectangleShape.h"


using namespace RendUI;

RoundedRectangleShape::RoundedRectangleShape(const sf::Vector2f& size, float radius, unsigned int cornerPointCount)
	: m_size(size), m_radius(radius), m_cornerPointCount(cornerPointCount)
{
	update();
}

void RoundedRectangleShape::setSize(const sf::Vector2f& size) {
	m_size = size;
	update();
}

const sf::Vector2f& RoundedRectangleShape::getSize() const {
	return m_size;
}

void RoundedRectangleShape::setRadius(float radius) {
	m_radius = radius;
	update();
}

float RoundedRectangleShape::getRadius() const {
	return m_radius;
}

void RoundedRectangleShape::setCornerPointCount(unsigned int count) {
	m_cornerPointCount = count;
	update();
}

unsigned int RoundedRectangleShape::getCornerPointCount() const {
	return m_cornerPointCount;
}

std::size_t RoundedRectangleShape::getPointCount() const {
	return m_cornerPointCount * 4;
}

sf::Vector2f RoundedRectangleShape::getPoint(std::size_t index) const {
	float angleStep = 90.f / (m_cornerPointCount - 1);
	float radius = m_radius;

	// 4 угла: 0 Ч верхний левый, 1 Ч верхний правый, 2 Ч нижний правый, 3 Ч нижний левый
	int corner = index / m_cornerPointCount;
	float localAngle = angleStep * (index % m_cornerPointCount);

	sf::Vector2f center;
	switch (corner) {
	case 0: center = { radius, radius }; localAngle += 180.f; break; // top-left
	case 1: center = { m_size.x - radius, radius }; localAngle += 270.f; break; // top-right
	case 2: center = { m_size.x - radius, m_size.y - radius }; localAngle += 0.f; break; // bottom-right
	case 3: center = { radius, m_size.y - radius }; localAngle += 90.f; break; // bottom-left
	}

	float rad = localAngle * 3.14159265f / 180.f;
	return { center.x + std::cos(rad) * radius, center.y + std::sin(rad) * radius };
}