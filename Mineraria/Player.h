#pragma once

#include "Entity.h";
#include "Inventory.h"
#include "GameSettings.h"

class Player : public Entity
{
private:
	Inventory* inv;

public:
	Player();
	~Player() = default;
	Vector2f getCenter();
	Inventory draw_inv();
	void update();
	
};

