#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet
{
private:

	sf::Sprite shape;


	sf::Vector2f direction;
	float movementSpeed;

public:

	Bullet(sf::Texture* texture, float posx, float posy, float dirX, float dirY, float movementSpeed);
	~Bullet();

	const sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderTarget* target);
};

