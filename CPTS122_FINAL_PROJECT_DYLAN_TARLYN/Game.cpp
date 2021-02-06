#include "Game.h"

/*
	Initializes the window and it's properties such as title, screen size, v sync, and fps cap
*/
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800,900),"Star Wars: Episode X - The Polygons Strike Back",sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144); // caps the frame rate so player doesn't move faster at hihger fps
	this->window->setVerticalSyncEnabled(false); // disable vsync
}

/*	
	Initializes the player
*/

void Game::initPlayer()
{
	this->player = new Player();
	// centers the player
	this->player->setPosition(
		this->window->getSize().y / 2.f - this->player->getBounds().width, this->window->getSize().x / 2.f);
}

/*
	Initializes the bullet texture
*/
void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture(); // creating texture for bullets
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

/*
	Initializes enemeies and their spawn rate
*/

void Game::initEnemies()
{
	this->spawnTimeMax = 50.f; // used to change spwan rate, higher is slower
	this->spawnTime = this->spawnTimeMax;
}

/*
	Initializes the different graphics for the user interface
*/

void Game::initGUI()
{
	// font
	this->font.loadFromFile("Fonts/RetroGaming.ttf");

	// points text settings
	this->pointCounter.setFont(this->font); // set the font
	this->pointCounter.setCharacterSize(24); // set size
	this->pointCounter.setFillColor(sf::Color::White); // set the color
	this->pointCounter.setString("Points: "); // set the string

	// game over settings

	this->gameOver.setFont(this->font); // set the font
	this->gameOver.setCharacterSize(65); // set size
	this->gameOver.setFillColor(sf::Color::Red); // set the color
	this->gameOver.setString("GAME OVER"); // set the string

	//game over text display settins

	this->gameOver.setPosition(
		this->window->getSize().x / 2.f - this->gameOver.getGlobalBounds().width / 2.f, // center x axis
		this->window->getSize().y / 2.f - this->gameOver.getGlobalBounds().height / 2.f); // center y axis

		// escape text
	this->escape.setFont(this->font); // set the font
	this->escape.setCharacterSize(30); // set size
	this->escape.setFillColor(sf::Color::Red); // set the color
	this->escape.setString("PRESS ESC TO EXIT"); // set the string

	//escape text display settins

	this->escape.setPosition(
		this->window->getSize().x / 2.f - this->escape.getGlobalBounds().width / 2.f, // center x axis
		this->window->getSize().y / 2.f - this->escape.getGlobalBounds().height / 2.f + 70); // center y axis and move below

	// continue text
	this->con.setFont(this->font); // set the font
	this->con.setCharacterSize(30); // set size
	this->con.setFillColor(sf::Color::Green); // set the color
	this->con.setString("PRESS ENTER TO CONTINUE"); // set the string

	//continue text display settins

	this->con.setPosition(
		this->window->getSize().x / 2.f - this->con.getGlobalBounds().width / 2.f, // center x axis
		this->window->getSize().y / 2.f - this->con.getGlobalBounds().height / 2.f+120); // center y axis and move below

	// restart game text

	// restart text
	this->restart.setFont(this->font); // set the font
	this->restart.setCharacterSize(30); // set size
	this->restart.setFillColor(sf::Color::White); // set the color
	this->restart.setString("PRESS R TO RESTART"); // set the string

	//restart text display settins

	this->restart.setPosition(
		this->window->getSize().x / 2.f - this->restart.getGlobalBounds().width / 2.f, // center x axis
		this->window->getSize().y / 2.f - this->restart.getGlobalBounds().height / 2.f + 170); // center y axis and move below





	// Player GUI

	this->healthBar.setSize(sf::Vector2f(300.f, 25.f)); // size of health bar
	this->healthBar.setFillColor(sf::Color::Red); // color of health bar
	this->healthBar.setPosition(sf::Vector2f(0.f, 100.f)); // position of health bar

	this->healthBarBack = this->healthBar;
	this->healthBarBack.setFillColor(sf::Color::White); // color of back of health bar

}

/*
	Initializes the background image
*/

void Game::initBackground()
{
	this->backgroundTexture.loadFromFile("Textures/background.jpg");
	this->background.setTexture(this->backgroundTexture);
}

/*
	Initializes any sort of value we want to track, for this program we only track points
*/

void Game::initSystems()
{
	this->points = 0;
}

/*
	Game constructor where all the pieces are initialized
*/

Game::Game()
{
	this->initWindow(); // initialize the window
	this->initTextures(); // initializes the textures
	this->initGUI(); // initializes the GUI
	this->initSystems(); // initializes extra systems functions
	this->initPlayer(); // initialize the player
	this->initEnemies(); // initalize the enemies
	this->initBackground(); /// initailizes the background
}

/*
	Desctructor where everything is deleted and closed so we don't have any memory leak
*/

Game::~Game()
{
	delete this->window;
	delete this->player;

	// remove textures at the end of game

	for (auto& i : this->textures) { // for each string

		delete i.second; // deleting part that actually contains the texture
	}

	for (auto* i : this->bullets) { // clears all bullets
		delete i;
	}

	// delete enemies

	for (auto* i : this->enemies) {
		delete i;
	}
}


//	FUNCTIONS

/*
	This function runs the game
*/

void Game::run()
{
	while (this->window->isOpen()) { // while the window is open
		if (this->player->getHealth() > 0) { // if the player health is above zero
			this->update(); // run all of our update functons
			this->render(); // run all of our render functions
		}
		// end game conditions
		else {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) // if the escape key is pressed
				this->window->close(); // close the window
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
				this->player->setHealth(100);
				this->player->setPosition( // re-center the player
					this->window->getSize().y / 2.f - this->player->getBounds().width, this->window->getSize().x / 2.f);

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
				this->player->setHealth(100); //reset health
				this->points = 0;// reset points
				this->player->setPosition( // re-center the player
					this->window->getSize().y / 2.f - this->player->getBounds().width, this->window->getSize().x / 2.f);
			}

			//allows the user to click the X button at the top

			sf::Event e;

			while (this->window->pollEvent(e)) {
				if (e.Event::type == sf::Event::Closed)
					this->window->close();
			}
		}
	}
}

/*
	This function runs all of our different update functions
	It's important to run them in this order so it doesn't crash
*/

void Game::update()
{
	this->updateInput();

	this->player->update();

	this->updateCollision();

	this->updateBullets();

	this->updateEnemies();

	this->updateGUI();

}

/*
	This function runs all of our different render functions such as rendering the player, bullets, enemies
	It's important to run them in this order so it doesn't crash
*/

void Game::render()
{
	this->window->clear(); // clears the frame

	// background

	this->renderBackground(); // render the background

	// player

	this->player->render(*this->window); // render the player in the window

	// bullets

	for (auto* bullet : this->bullets) { // render the bullets in the window
		bullet->render(this->window); 
	}

	// enemies

	for (auto* enemy : this->enemies) { // render the enemies in the window
		enemy->render(this->window);
	}

	// GUI

	this->renderGUI(); // render all of our GUI stuff

	// Game Over

	if (this->player->getHealth() <= 0) { // if the player reaches 0 health
		this->window->draw(this->gameOver); // show the game over text
		this->window->draw(this->con); // continue text
		this->window->draw(this->restart); // restart
		this->window->draw(this->escape); // close game
	}

	this->window->display(); // displays what we drew depending on the case
}

/*
	This function renders our GUI which consists of the points counter and the health bar
*/

void Game::renderGUI()
{
	this->window->draw(this->pointCounter);

	this->window->draw(this->healthBarBack);
	this->window->draw(this->healthBar);
}

/*
	This function renders our background image that we set
*/
void Game::renderBackground()
{
	this->window->draw(this->background);
}

/*
	This function takes user input and moves the ship, fires bullets, or closes the game
	We can also change bullet settings here
*/

void Game::updateInput()
{
	// Move player

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) // left
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) // right
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) // up
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) // down
		this->player->move(0.f, 1.f);

	// Bullets
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && this->player->canAttack()){ // when the spacebar is pressed
		// fire a bullet from the center player position
		this->bullets.push_back(
			new Bullet(this->textures["BULLET"], // make a new bullet with the texture we set
			this->player->getPos().x + this->player->getBounds().width/2.f, // put it in the center of the player position horizontally
			this->player->getPos().y, // center it vertically
			0.f,-1.f,5.f)); // the direction the bullet goes and at what speed (change last number for speed, higher is faster)
	}

	//escape

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) // if the escape key is pressed
		this->window->close(); // close the window

	// Window

	sf::Event e;

	while (this->window->pollEvent(e)) {
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
	}

}

/*
	This function updates our GUI by showing updated points and health
*/

void Game::updateGUI()
{
	std::stringstream ss; // string variable

	ss <<"Points: "<< this->points << "\n\nHealth"; // displays to the screen

	this->pointCounter.setString(ss.str()); // settin the counter to interac with the string

	// Player GUI
	
	// updates the health bar against the background
	float healthPercent = static_cast<float>(this->player->getHealth()) / this->player->getHealthMax();
	this->healthBar.setSize(sf::Vector2f(300.f *healthPercent , this->healthBar.getSize().y));

}

/*
	This function updates our bullets and makes sure they don't take up memory once they leave the screen
*/

void Game::updateBullets()
{

	unsigned count = 0; // can't go below zero

	for (auto* bullet : this->bullets) {
		bullet->update(); // update our bullet

		//when bullet reaches top of the screen

		if (bullet->getBounds().top + bullet->getBounds().height < 0.f) { // if the bullet goes off the sreen

			delete this->bullets.at(count); // delete bullet

			this->bullets.erase(this->bullets.begin() + count); // erase from the vector
		}
		++count; // increase our count by one
	}
}

/*
	This function updates our enemies and how they interact with other things on the screen
*/

void Game::updateEnemies()
{
	this->spawnTime += 0.7f; // how fast the enemies spawn (higher is faster)

	if (this->spawnTime >= this->spawnTimeMax) { // when it reaches the max
		this->enemies.push_back(new Enemy(rand() % // random spawn seed / where they spawn
			this->window->getSize().x+0.f, // anywhere within window width plus a litle to the right so you can still hit them
			-100.f)); // at the top of the screen
		this->spawnTime = 0.f; // reset the timer
	}

	//removing enemies from the game

	for (int i = 0; i < this->enemies.size(); ++i) {

		bool isRemoved = false; // is the enemy removed from the screen

		this->enemies[i]->update();

		// delete enemy and bullet if they intersect

		for (size_t k = 0; k < this->bullets.size() && !isRemoved; k++) {
			if (this->bullets[k]->getBounds().intersects(this->enemies[i]->getBounds())) {

				this->points += this->enemies[i]->getPoints();

				this->bullets.erase(this->bullets.begin() + k); // erase bullets from vector
				this->enemies.erase(this->enemies.begin() + i); // erase enemies from vector

				isRemoved = true; // yes they have been removed
			}
		}


		// other cases for deleted the enemy
		if (!isRemoved) {

			// if enemy collides with player
			if (enemies[i]->getBounds().intersects(this->player->getBounds())) {

				this->player->loseHealth(this->enemies[i]->getDamage()); // lose health

				delete this->enemies[i]; // delete the enemy
				this->enemies.erase(this->enemies.begin() + i); // erase it from the vector
			}

			// if enemy reaches the bottom

			else if (this->enemies[i]->getBounds().top > this->window->getSize().y){
				this->enemies.erase(this->enemies.begin() + i); // erase from the vector
				isRemoved = true; // yes the enemy has been removed
			}
		}
	}
}

/*
	This function makes sure that the player stays on the screen
*/
void Game::updateCollision()
{
	// Left collision

	if (this->player->getBounds().left < 0.f) {
		this->player->setPosition(0.f, this->player->getBounds().top);
	}

	// Right Collision

	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x) {
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}
	
	// top collision

	if (this->player->getBounds().top < 0.f) {
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	
	// bottom collision

	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y) {
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}
