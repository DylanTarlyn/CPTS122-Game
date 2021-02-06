#pragma once
#include <string>
#include <sstream>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include <map>

class Game
{
private:
	// resources
	std::map<std::string, sf::Texture*> textures; // maps textures to string
	std::vector<Bullet*> bullets; // creates a bullet vector

	// window
	sf::RenderWindow* window;

	// player
	Player* player;
	sf::RectangleShape healthBar;
	sf::RectangleShape healthBarBack;

	// enemies
	std::vector<Enemy*> enemies; // enemy vector
	float spawnTime;
	float spawnTimeMax;


	// init functions
	void initWindow();
	void initPlayer();
	void initTextures();
	void initEnemies();
	void initGUI();
	void initBackground();
	void initSystems();

	// GUI
	sf::Font font;
	sf::Text pointCounter;
	sf::Text gameOver;
	sf::Text con; // continue with same score
	sf::Text restart;
	sf::Text escape;

	// Extra
	sf::Texture backgroundTexture; // background image
	sf::Sprite background; // displays the image
	
	// Systems
	unsigned points; // can't be less than 0


public: 
	Game(); // constructor
	~Game(); // desctructor

	void run(); // run function
	void update(); // updates each frame
	void render(); // draws at updated positions
	void renderGUI(); // renders GUI
	void renderBackground(); // renders background image
	
	// individual update function
	void updateInput();
	void updateGUI();
	void updateBullets();
	void updateEnemies();
	void updateCollision();



};

