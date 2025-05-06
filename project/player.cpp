#include "sgg/graphics.h"
#include "player.h"
#include "gamestate.h"

void Player::movePlayer(float dt)
{

	float delta_time = dt / 1000.0f;


	float move = 0.0f;
	//Otan kinite aristera 
	if (graphics::getKeyState(graphics::SCANCODE_A))
		move -= 1.0f;
	if (graphics::getKeyState(graphics::SCANCODE_D))
		move += 1.0f;

	// orizontia kinisi
	// Olokliroma tis epitaxinsis epi ton xrono gia dexia kinisi
	m_vx =std::min(m_max_velocity, m_vx + delta_time * move * m_accel_horizontal);
	//Gia aristera
	m_vx =std::max(-m_max_velocity, m_vx );

	m_vx -= 0.2f * m_vx/(0.1f + fabs(m_vx));
	if (fabs(m_vx) < 0.01f)
		m_vx = 0.0f;
	//Thesi einai taxitita * xrono 
	m_pos_x += delta_time * m_vx;

	//Varituta 
	// Katheti kinisi 
	if (m_vy == 0.0f)
		m_vy -= graphics::getKeyState(graphics::SCANCODE_W) ? m_accel_vertical : 0.0f;
	m_vy += delta_time * m_gravity;

	m_pos_y += m_vy * delta_time;
}

void Player::update(float dt)
{

	movePlayer(dt);

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;
	setDirectionImage();

}

void Player::init()
{
	m_pos_x = 5.0f;
	m_pos_y = 5.0f;

	// Gia * sta cubes (oria)
	m_width /= 2.0f;

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	m_brush_player.fill_opacity = 1.0f;
	m_brush_player.outline_opacity = 0.0f;
	m_brush_player.texture = m_state->getFullAssetPath("Mini_Mario.png");
}

void Player::draw()
{
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 1.0f, 1.0f, m_brush_player);

}

void Player::setDirectionImage() {
	// Moving left
	if (m_vx < 0) {
		m_brush_player.texture = m_state->getFullAssetPath("Mini_Mario2.png");
	}
	// Moving right
	else if (m_vx > 0) { 
		m_brush_player.texture = m_state->getFullAssetPath("Mini_Mario.png");
	}
	// If m_vx == 0, looking straight
}

void Player::setPosition(float x, float y) {
	m_pos_x = x;
	m_pos_y = y;
}