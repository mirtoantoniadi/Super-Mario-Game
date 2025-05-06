#include "gamestate.h"
#include "level.h"
#include "player.h"
#include  <thread>
#include <chrono>
#include <iostream>

GameState::GameState()
{
}

void GameState::init()
{
	m_current_level = new Level();
	m_current_level->init();

	m_player = new Player("Mario");
	m_player->init();

	graphics::preloadBitmaps(getAssetDir());
}

void GameState::draw()
{

	if (!m_current_level)
		return;

	m_current_level->draw();
}

void GameState::checkWinCondition()
{
	if (m_player && m_player->getPositionX() > 44.0f) {
		isGameWon = true;
	}
}


void GameState::update(float dt)
{

	// std::cout << "Mario Y: " << m_player->m_pos_y << std::endl;
	// Ensures updates do not run for excessively long frames
	if (dt > 500)
		return;

	// Update the current level and player
	if (m_current_level)
	{
		m_current_level->update(dt);
	}

	// Implement Mario's death logic due to falling
	float deathYPosition = 7.0f;
	if (m_player && m_player->isActive() && m_player->m_pos_y > deathYPosition) {
		// Mark for death due to falling
		m_player->markForDeath(); 
	}

	// Check if the player is marked for death and handle it
	if (m_player && m_player->shouldDie()) {
		handleMarioDeath();
		// Reset the flag after handling death
		m_player->resetDeathFlag(); 
	}

	m_debugging = graphics::getKeyState(graphics::SCANCODE_0);

	checkWinCondition();
	
}




void GameState::resetGame() {
	if (m_current_level) {
		// Delete the current level to free up memory
		delete m_current_level; 
		// Create a new level instance
		m_current_level = new Level(); 
		// Initialize the new level
		m_current_level->init(); 
	}

	if (m_player) {
		// Reset player's position to the start
		m_player->setPosition(5.0f, 5.0f); 
		// Make sure the player is active
		m_player->setActive(true); 
		// Re-initialize player to reset any state
		m_player->init(); 
	}


	
}

void GameState::gameOver() {
	
	isGameOver = true;
}



void GameState::handleMarioDeath() {
	// Decrement the life count
	m_playerLives--; 

	if (m_playerLives > 0) {
		// Reset the game while keeping the lives count updated
		// std::cout << "Reset";
		resetGame();
	}
	else {
		// No lives left, show the game over screen
		gameOver();
	}
}

GameState* GameState::getInstance()
{
	if (m_unique_instance == nullptr)
		m_unique_instance = new GameState();

	return m_unique_instance;
}

GameState::~GameState()
{
	if (m_player)
		delete m_player;
	if (m_current_level)
		delete m_current_level;
}

std::string GameState::getAssetDir()
{
	return m_asset_path;
}

std::string GameState::getFullAssetPath(const std::string& asset)
{
	return m_asset_path + asset;
}


GameState* GameState :: m_unique_instance=nullptr;
