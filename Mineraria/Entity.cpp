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
	const double g = 160.0;//hiden 
	velocity.y = velocity.y + g * 0.025;
}

void Entity::updatePosition(int top, int down, int left, int right)
{
	Vector2f pos = getPosition();
	if ((pos.y + entity.getGlobalBounds().height + velocity.y * 0.025) > down)
	{
		if (velocity.y > 100)
		{
			health -= (((velocity.y-100) / 16) +((velocity.y-100)* (velocity.y - 100) )/128);
			std::cout<<"damage: "<<(((velocity.y-100) / 16) + ((velocity.y - 100) * (velocity.y - 100)) / 128)<<std::endl;
		}
		velocity.y = 0;
		//pos.y = down - entity.getGlobalBounds().height-1;
	}
	else
	{
		applyGravity();
	}
	if (pos.y + velocity.y * 0.025 < top)
	{
		velocity.y *=-0.25;
		//pos.y = top+1;
	}
	if (entity.getGlobalBounds().left + velocity.x * 0.025 < left)
	{
		velocity.x = 0;
		//pos.x = left+1;
	}else if (entity.getGlobalBounds().left + entity.getGlobalBounds().width + velocity.x * 0.025 > right)
	{
		velocity.x = 0;
		//pos.x = right - entity.getGlobalBounds().width-1;
	}
	else
	{
		pos.x = pos.x + velocity.x * 0.025;
	}

	pos.y = pos.y + velocity.y * 0.025;

	entity.setPosition(pos);
}

FloatRect Entity::getHitBox()
{
	return entity.getGlobalBounds();
}