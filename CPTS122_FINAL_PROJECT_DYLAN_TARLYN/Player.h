#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>

class Player
{
private:

	sf::Sprite sprite; // displaying the texture
	sf::Texture texture; // holds a texture

	float movementSpeed;

	float attackCooldown; // adding to cooldown
	float attackCooldownMax; // reaching the cooldown

	int health;
	int healthMax;

	void initVariables();
	void initTexture();
	void initSprite();



public:
	Player(); // constructor
	~Player(); // desctructor

	const sf::Vector2f& getPos() const; // get position of player
	sf::FloatRect getBounds() const; // get bounds of player
	const int& getHealth() const;
	const int& getHealthMax() const;

	void update();
	void render(sf::RenderTarget& target);

	void move(const float dirX, const float dirY);
	const bool canAttack();

	void updateAttack();

  // player attributes
	void setPosition(const float x, const float y); // position
	void setHealth(const int health); // setting health
	void loseHealth(const int val);  // losing health
};

