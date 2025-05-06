#include "level.h"
#include "gamestate.h"
#include "player.h"
#include "util.h"
#include <iostream>




// Gia ta cubes
void Level::drawBlock(int i)
{
	Box& box = m_blocks[i];
	float x = box.m_pos_x+ m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;
	m_block_brush.texture = m_state->getFullAssetPath(m_block_names[i]);
	graphics::drawRect(x, y,m_block_size,m_block_size,m_block_brush);

	if(m_state->m_debugging)
		graphics::drawRect(x, y, m_block_size, m_block_size, m_block_brush_debug);

}

void Level::checkCollisions()
{

	// Na epanaferei tin thesi tou player gia ta cubes 
	for (auto& box : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectDown(box))
		{
			m_state->getPlayer()->m_pos_y += offset;
			m_state->getPlayer()->m_vy = 0.0f;
			break;

		}

	}

	for (auto& box : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectSideways(box))
		{
			m_state->getPlayer()->m_pos_x += offset;
			if (m_state->getPlayer()->m_vx > 1.0f)
				graphics::playSound(m_state->getFullAssetPath("metal2.wav"), 0.5f);


			m_state->getPlayer()->m_vx = 0.0f;
			break;

		}

	}

	Player* player = m_state->getPlayer();

	for (auto& obj : m_dynamic_objects) {
		MiniMushroom* item = dynamic_cast<MiniMushroom*>(obj);
		if (item && item->isActive() && item->intersect(*m_state->getPlayer())) {
			// Handle coin collection
			if (item->getType() == "coin") {
				item->onCollision(m_state->getPlayer());
			}
			// For mushrooms, we first check side collision which should result in Mario's death
			else if (item->getType() == "mushroom") {
				if (m_state->getPlayer()->intersectSideways(*item)) {
					m_state->getPlayer()->markForDeath();
					break; // Exit the loop if Mario die
				}
				else if (m_state->getPlayer()->intersectDown(*item)) {
					item->onCollision(m_state->getPlayer());
				}
			}
		}
	}


	
}

void Level::spawnCoins() {
	MiniMushroom* coin1 = new MiniMushroom("coin1", "coin");
	// Set position
	coin1->setPosition(6.0f, 4.0f);
	// Specify the image for the coin
	coin1->setImage("coin.png"); 
	coin1->init();
	m_dynamic_objects.push_back(coin1);

	MiniMushroom* coin2 = new MiniMushroom("coin2", "coin");
	coin2->setPosition(7.0f, 4.0f); 
	coin2->setImage("coin.png"); 
	coin2->init();
	m_dynamic_objects.push_back(coin2);

	MiniMushroom* coin3 = new MiniMushroom("coin3", "coin");
	coin3->setPosition(8.0f, 4.0f);
	coin3->setImage("coin.png"); 
	coin3->init();
	m_dynamic_objects.push_back(coin3);

	MiniMushroom* coin4 = new MiniMushroom("coin4", "coin");
	coin4->setPosition(9.0f, 4.0f);
	coin4->setImage("coin.png"); 
	coin4->init();
	m_dynamic_objects.push_back(coin4);

	MiniMushroom* coin5 = new MiniMushroom("coin5", "coin");
	coin5->setPosition(19.0f, 4.0f); 
	coin5->setImage("coin.png");
	coin5->init();
	m_dynamic_objects.push_back(coin5);

	MiniMushroom* coin10 = new MiniMushroom("coin10", "coin");
	coin10->setPosition(20.0f, 3.0f);
	coin10->setImage("coin.png"); 
	coin10->init();
	m_dynamic_objects.push_back(coin10);

	MiniMushroom* coin6 = new MiniMushroom("coin6", "coin");
	coin6->setPosition(21.0f, 2.0f); 
	coin6->setImage("coin.png"); 
	coin6->init();
	m_dynamic_objects.push_back(coin6);

	MiniMushroom* coin7 = new MiniMushroom("coin7", "coin");
	coin7->setPosition(22.0f, 1.0f); 
	coin7->setImage("coin.png"); 
	coin7->init();
	m_dynamic_objects.push_back(coin7);

	MiniMushroom* coin8 = new MiniMushroom("coin8", "coin");
	coin8->setPosition(34.0f, 2.0f); 
	coin8->setImage("coin.png"); 
	coin8->init();
	m_dynamic_objects.push_back(coin8);

	MiniMushroom* coin9 = new MiniMushroom("coin9", "coin");
	coin9->setPosition(35.0f, 1.0f); 
	coin9->setImage("coin.png"); 
	coin9->init();
	m_dynamic_objects.push_back(coin9);

}

void Level::update(float dt)
{
	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->update(dt);

	checkCollisions();
	for (auto& obj : m_dynamic_objects) {
		obj->update(dt);
	}



	GameObject::update(dt);
}

void Level::init()
{
	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = m_state->getFullAssetPath("background3.png");

	for (auto p_gob : m_static_objects)
		if (p_gob) p_gob->init();

	for(auto p_gob : m_dynamic_objects)
		if (p_gob) p_gob->init();

	m_blocks.push_back(Box(4 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(5* m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(6 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(7 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(8 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(9 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(10 * m_block_size, 5 * m_block_size, m_block_size, m_block_size)); //solinas
	m_blocks.push_back(Box(10 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(11 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(12 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(15 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(16 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(17 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(17 * m_block_size, 5 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(18 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(19 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(21 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(23 * m_block_size, 2 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(25 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(26 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(27 * m_block_size, 3 * m_block_size, m_block_size, m_block_size)); //solinas
	m_blocks.push_back(Box(27 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(28 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(29 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(31 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(32 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(33 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(34 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(36 * m_block_size, 2 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(37 * m_block_size, 2 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(38 * m_block_size, 2 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(39 * m_block_size, 2 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(42 * m_block_size, 2 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(43 * m_block_size, 2 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(44 * m_block_size, 1 * m_block_size, m_block_size, m_block_size)); // edo einai i simea
	m_blocks.push_back(Box(44 * m_block_size, 2 * m_block_size, m_block_size, m_block_size)); 
	m_blocks.push_back(Box(45 * m_block_size, 2 * m_block_size, m_block_size, m_block_size));
	


	
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("solinas.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("solinas.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("solinas.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("flag.png");
	m_block_names.push_back("cube1.png");
	m_block_names.push_back("cube1.png");
	

	m_block_brush.outline_opacity = 0.0f;

	m_block_brush_debug.fill_opacity = 0.1f;
	SETCOLOR(m_block_brush_debug.fill_color, 0.2f, 1.0f, 0.1f);
	SETCOLOR(m_block_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);

	spawnMiniMushrooms();
	spawnCoins();
	
}




void Level::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	// Update the background texture based on game over state
	if (m_state->isGameOver) {
		m_brush_background.texture = m_state->getFullAssetPath("gameover.png");

		// Draw the game over background
		float offset_x = w / 2.0f;
		float offset_y = h / 2.0f;
		graphics::drawRect(offset_x, offset_y, w, h, m_brush_background);
	}
	else if (m_state->isGameWon) {
		m_brush_background.texture = m_state->getFullAssetPath("win.png");

		// Draw the win background
		float offset_x = w / 2.0f;
		float offset_y = h / 2.0f;
		graphics::drawRect(offset_x, offset_y, w, h, m_brush_background);
	}
	else {
		m_brush_background.texture = m_state->getFullAssetPath("background3.png");
		// Sxediazei kentrarismena 
		float offset_x = m_state->m_global_offset_x / 2.0f + w / 2.0f;
		float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;

		// Draw to background				// 2.0f * w , 4.0f *w 
		graphics::drawRect(offset_x, offset_y, 8.0f * w, 2.0f * w, m_brush_background);

		
		// Alla stoixeia piso apo ton paixti 
		for (int i = 0; i < m_blocks.size(); i++)
		{
			drawBlock(i);
		}

		if (m_state->getPlayer()->isActive())
			m_state->getPlayer()->draw();

		// Alla stoixeia brosta apo ton paixti 

		for (auto p_gob : m_static_objects)
			if (p_gob) p_gob->draw();

		for (auto p_gob : m_dynamic_objects)
			if (p_gob) p_gob->draw();

		

		
	}
	

	
}

Level::Level(const std::string& name)
{
}

Level::~Level()
{
	for (auto p_gob : m_static_objects)
		if (p_gob) delete p_gob;

	for (auto p_gob : m_dynamic_objects)
		if (p_gob) delete p_gob;

	
}

void Level::spawnMiniMushrooms() {
	MiniMushroom* miniMushroom = new MiniMushroom("miniMushroom", "mushroom");

	// Y-coordinate 
	float tubeX = 9.0f; 
	// X-coordinate 
	float cubeX = 4.0f;  
	// Midpoint coordinate
	float mushroomX = (tubeX + cubeX) / 2.0f; 
	float mushroomY = 5.0f; 

	// Set the position of the Mini Mushroom
	miniMushroom->setPosition(mushroomX, mushroomY);

	// Set horizontal movement boundaries 
	miniMushroom->setBoundaries(cubeX, tubeX); 

	miniMushroom->setSpeed(2.0f); 
	miniMushroom->setDirection(1); 

	miniMushroom->setImage("goomba.png");
	miniMushroom->init();
	m_dynamic_objects.push_back(miniMushroom);


	MiniMushroom* sumo = new MiniMushroom("sumo", "mushroom");

	float tubesX = 31.0f; 
	float cubesX = 34.0f; 
	float sumoX = (tubesX + cubesX) / 2.0f; 
	float sumoY = 3.0f; 

	// Set the position of Sumo
	sumo->setPosition(sumoX, sumoY);

	
	sumo->setBoundaries(tubesX, cubesX);
	sumo->setSpeed(2.0f); 
	sumo->setDirection(1); 

	sumo->setImage("Sumo.png");
	sumo->init();
	m_dynamic_objects.push_back(sumo);


	MiniMushroom* goomba = new MiniMushroom("goomba", "mushroom");

	float tubesX2 = 36.0f; 
	float cubesX2 = 39.0f;  
	float sumoX2 = (tubesX2 + cubesX2) / 2.0f; 
	float sumoY2 = 1.0f; 

	// Set the position of goomba
	goomba->setPosition(sumoX2, sumoY2);

	// Set horizontal movement boundaries
	goomba->setBoundaries(tubesX2, cubesX2);
	goomba->setSpeed(2.0f); 
	goomba->setDirection(1); 

	goomba->setImage("goomba2.png");
	goomba->init();
	m_dynamic_objects.push_back(goomba);



}





