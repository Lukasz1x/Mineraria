#include "Entity.h"

Entity::Entity()
{
	
}

void Entity::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->entity);
}

void Entity::setVelocity(Vector2f speed)
{
	velocity = speed;
}

Vector2f Entity::getVelocity()
{
	return velocity;
}

Vector2f Entity::getPosition()
{
	return entity.getPosition();
}

void Entity::setPosition(Vector2f pos)
{
	entity.setPosition(pos);
}

void Entity::applyGravity()
{
	const double g = 160.0;
	velocity.y = velocity.y + g * 0.025;
}

void Entity::updatePosition()
{
	Vector2f pos = getPosition();
	pos.y = pos.y + velocity.y * 0.025;
	entity.setPosition(pos);
}