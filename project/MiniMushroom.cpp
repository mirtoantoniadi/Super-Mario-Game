#include "MiniMushroom.h"
#include <iostream>

MiniMushroom::MiniMushroom(const std::string& name, std::string type)
    : GameObject(name), m_type(type) {
    m_brush.fill_opacity = 1.0f;
    m_brush.outline_opacity = 0.0f;

    if (m_type == "coin") {
        m_width = 0.5f; 
        m_height = 0.5f;
       
    }
    else {
        m_width = 1.0f;
        m_height = 1.0f;
        m_speed = 1.0f; 
        m_direction = 1; 
    }
}


void MiniMushroom::update(float dt) {
    if (!isActive() || m_type == "coin") return; // Skip update logic for coins
    if (!isActive()) return;
    // Convert to seconds
    float delta_time = dt / 1000.0f; 

    m_pos_x += m_direction * m_speed * delta_time;

    // Boundary check
    if (m_pos_x < m_left_boundary || m_pos_x > m_right_boundary) {
        m_direction = -m_direction;
        m_pos_x = std::max(m_left_boundary, std::min(m_pos_x, m_right_boundary));
    }
}




void MiniMushroom::draw() {
    if (!isActive()) return;
        graphics::drawRect(m_pos_x + m_state->m_global_offset_x, m_pos_y + m_state->m_global_offset_y, m_width, m_height, m_brush);

    
}



void MiniMushroom::onCollision(Player* player) {
    // Deactivate the enemies when Mario lands on it
    setActive(false); 
}

void MiniMushroom::setBoundaries(float left, float right) {
    m_left_boundary = left;
    m_right_boundary = right;
}


void MiniMushroom::setSpeed(float speed) {
    m_speed = speed;
}

void MiniMushroom::setPosition(float x, float y) {
    m_pos_x = x;
    m_pos_y = y;
    
}

void MiniMushroom::setDirection(int direction) {
    m_direction = direction;
}

void MiniMushroom::setImage(const std::string& image_name) {
    // Set the image
    m_brush.texture = m_state->getFullAssetPath(image_name);
}
