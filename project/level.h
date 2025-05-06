#pragma once
#include "player.h"
#include "sgg/graphics.h"
#include <list>
#include <vector>
#include <string>
#include "MiniMushroom.h"

class Level : public GameObject
{
	graphics::Brush m_brush_background;

	float m_center_x = 5.0f;
	float m_center_y = 5.0f;
	const float m_block_size = 1.0f;

	std::vector<GameObject*> m_static_objects;
	std::list<GameObject*> m_dynamic_objects;

	std::vector<Box> m_blocks;
	std::vector<std::string> m_block_names;
	graphics::Brush m_block_brush;
	graphics::Brush m_block_brush_debug;
	

	void drawBlock(int i);

	void checkCollisions();

	// Method to spawn mini mushrooms
	void spawnMiniMushrooms(); 
	

public:
	// Na enimeronei
	void update(float dt) override;
	// Fortonei kai xtizei to perivallon pou paizo
	void init() override;
	// Na sxediazei ta panta
	void draw() override;
	Level(const std::string& name= "Level0");
	~Level() override ;
	void spawnCoins();
	
};