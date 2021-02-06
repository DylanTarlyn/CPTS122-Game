#include "Player.h"

/*
	This function is used to initialize our variables which we can use as player settings
*/

void Player::initVariables()
{
	this->movementSpeed = 5.f; // player movement speed
	this->attackCooldownMax = 10.f; // how fast you can shoot (higher is slower)
	this->attackCooldown = this->attackCooldownMax;

	this->healthMax = 100; // maximum health
	this->health = this->healthMax; // initialize health as the max
}

/*
	This function initializs our ships texture
*/
void Player::initTexture()
{
	// load texture from file
	this->texture.loadFromFile("Textures/ship.png");
}

/*
	This functon initializes our sprite settings and allows us to change the height and width of the ship
	if our png is too big
*/

void Player::initSprite()
{
	// set texture to sprite
	this->sprite.setTexture(this->texture);

	// settin the size of the sprite
	this->sprite.scale(0.15f, 0.15f); // scaling the height and width
}

/*
	Constructor that initialzies player attributes
*/
Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();

}

// Destructor doesn't need to do anything
Player::~Player()
{
}

/*
 This function returns the players position
*/
const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition(); // used to get player position
}

/*
	This function returns the bounding box around the player
*/

sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds(); // get the bounds of the player
}

/*
	This function returns the players health
*/

const int& Player::getHealth() const
{
	return this->health;
}

/*
	This function returns the players max health
*/

const int& Player::getHealthMax() const
{
	return this->healthMax;
}


// MAIN FUNCTIONS

/*
	This function updates anything we need to update about the player
*/
void Player::update()
{
	this->updateAttack();
}

/*
	This function renders anything we need to about the player
*/

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

/*
	This function allows the player to move in an x and y direction
*/

void Player::move(const float dirX, const float dirY)
{

	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

/*
	This function sets a cooldown so they player can't fire constantly
*/

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax) {
		this->attackCooldown = 0.f; //resets the cooldown
		return true;
	}

	return false;
}

/*
	This function changes how long the coooldown is
*/

void Player::updateAttack()
{
	if(this->attackCooldown < this->attackCooldownMax) // if cooldown hasn't reached max
		this->attackCooldown += .5f; // add to cooldown, higher is faster
}

/*
	This function sets the position for the player
*/

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

/*
	This function sets the player health
*/

void Player::setHealth(const int health)
{
	this->health = health;
}

/*
	This function makes the player lose health
*/

void Player::loseHealth(const int val)
{
	this->health -= val;
	if (this->health < 0) {
		this->health = 0;
	}
}

