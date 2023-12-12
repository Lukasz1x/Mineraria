#pragma once

#include "Entity.h";

class Player : public Entity
{
public:
	Player();
	~Player() = default;
	Vector2f getCenter();
	
};

