#pragma once




namespace RendUI {

	class RoundedRectangleShape : public sf::Shape {
	public:
		RoundedRectangleShape(const sf::Vector2f& size = { 0.f, 0.f }, float radius = 0.f, unsigned int cornerPointCount = 8);

		void setSize(const sf::Vector2f& size);
		const sf::Vector2f& getSize() const;

		void setRadius(float radius);
		float getRadius() const;

		void setCornerPointCount(unsigned int count);
		unsigned int getCornerPointCount() const;

		std::size_t getPointCount() const override;
		sf::Vector2f getPoint(std::size_t index) const override;

	private:
		sf::Vector2f m_size;
		float m_radius;
		unsigned int m_cornerPointCount;
	};
}