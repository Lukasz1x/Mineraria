#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

class Entity : public Drawable
{
protected:
	void draw(RenderTarget& target, RenderStates state) const override;
	RectangleShape entity;
	int health, max_health;
	Texture entity_texture;
	Vector2f velocity = Vector2f(0.0f, 0.0f);
	Entity();
	~Entity() = default;
public:
	void setVelocity(Vector2f speed);
	Vector2f getVelocity();
	void setPosition(Vector2f pos);
	Vector2f getPosition();
	void applyGravity();
	void updatePosition();

};

