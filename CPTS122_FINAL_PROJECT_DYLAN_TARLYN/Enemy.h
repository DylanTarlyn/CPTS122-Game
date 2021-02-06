#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy
{

private:

	sf::CircleShape shape;

	float speed;
	int health;
	int healthMax;
	int damage;
	int score;

	unsigned pointsCount;

	void initShape();
	void initVariables();

public:

	Enemy(float posX, float posY);
	~Enemy();

	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	void update();
	void render(sf::RenderTarget* target);

};

