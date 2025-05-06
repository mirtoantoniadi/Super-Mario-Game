#pragma once

#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"

class Player :public GameObject ,public Box
{
	graphics::Brush m_brush_player;

	// Epitaxinseis 
	const float m_gravity = 10.0f;
	// Gia to alma 
	const float m_accel_vertical = 6.0f;
	const float m_accel_horizontal = 40.0f;
	const float m_max_velocity = 10.0f;


	void movePlayer(float dt);
	// Flag to mark the player for death
	bool m_shouldDie = false; 


public:

	float m_vx = 0.0f;
	float m_vy = 0.0f;
	Player(std::string name) : GameObject(name) {}

	void update(float dt) override;
	void init() override;
	void draw() override;
	void setDirectionImage();
	void setPosition(float x , float y);
	// Method to mark the player for death
	void markForDeath() {
		m_shouldDie = true;
	}

	// Method to check if the player is marked for death
	bool shouldDie() const {
		return m_shouldDie;
	}

	// Reset the death flag (for example, when the game is reset)
	void resetDeathFlag() {
		m_shouldDie = false;
	}

	float getPositionX() const { return m_pos_x; }

protected:
	void debugDraw();
	
};