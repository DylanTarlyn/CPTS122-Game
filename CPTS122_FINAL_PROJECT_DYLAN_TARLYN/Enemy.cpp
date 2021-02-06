#include "Enemy.h"


/*
	Initializes our enemies
*/
void Enemy::initShape()
{
	this->shape.setRadius(this->pointsCount * 5); // size and points are linked
	this->shape.setPointCount(this->pointsCount); // number of edges and points are linked


	// random opaque color
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, 255));
}

/*
 This contains our enemy settings
*/
void Enemy::initVariables()
{
	this->pointsCount = rand() % 8 + 3; // between 3-10 points
	this->speed = static_cast<float>(this->pointsCount/2); // speed of the enemies
	this->healthMax = static_cast<int>(this->pointsCount); // max health is the same as points
	this->health = this->healthMax;
	this->damage = this->pointsCount; // damage they do to player is same as points
	this->score = this->pointsCount; // how many points they give
}

/*
 Constructor for initializing the enemies
*/

Enemy::Enemy(float posX, float posY)
{
	this->initVariables();
	this->initShape();

	this->shape.setPosition(posX, posY);
}

/*
	No need for a destructor since they are deleted in Game.cpp
*/
Enemy::~Enemy()
{
}

/*
	Returns the bounding box of the enemy
*/

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds(); // return the bounds of the enemy
}

/*
	Returns the points each enemy gives
*/

const int& Enemy::getPoints() const
{
	return this->score;
}

/*
	Returns how much damage the enemy deals
*/

const int& Enemy::getDamage() const
{
	return this->damage;
}

/*
	Settings for how the enemies move
*/

void Enemy::update()
{
	this->shape.move(0.f, this->speed); // move down
}

/*
	Rendering the enemies
*/

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
