#pragma once

#include "Entity.h";

class Player : public Entity
{
public:
	Player();
	~Player() = default;
	Vector2f getCenter();
	void move_left();
	void move_right();
	
};

