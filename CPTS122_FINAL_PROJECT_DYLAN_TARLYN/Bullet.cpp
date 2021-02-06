#include "Bullet.h"

/*
	Constructor with our bullet settings
*/

Bullet::Bullet(sf::Texture* texture,float posx, float posy, float dirX, float dirY, float movementSpeed)
{
	this->shape.scale(.15f, .15f); // changes scale of the bullet

	this->shape.setTexture(*texture); // maps the texture to the shape
	this->shape.setPosition(posx, posy); // sets the positio
	this->direction.x = dirX;
	this->direction.y = dirY;
	this->movementSpeed = movementSpeed;
}

/*
	No need for a destuctor since the memory is freed in Game.cpp
*/
Bullet::~Bullet()
{

}

/*
	This function return the bounding box for the bullet
*/

const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

/*
	This function updates the bullet in any way we need it to
*/

void Bullet::update()
{
	// update movement

	this->shape.move(this->movementSpeed * this->direction);
}

/*
	This function renders the bullet onto the screen
*/
void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
