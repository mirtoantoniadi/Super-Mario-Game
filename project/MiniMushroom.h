#pragma once
#include "gameobject.h"
#include "box.h"
#include "player.h"
#include "sgg/graphics.h"
#include "gamestate.h"

class MiniMushroom : public GameObject, public Box {
    graphics::Brush m_brush;
    // Speed 
    float m_speed = 0.0f; 
    // Current moving direction (1 = right, -1 = left)
    int m_direction; 
    // Left boundary for movement
    float m_left_boundary; 
    // Right boundary for movement
    float m_right_boundary; 
    

public:
    MiniMushroom(const std::string& name, std::string type );
    void update(float dt) override;
    void draw() override;
    void onCollision(Player* player);

    void setBoundaries(float left, float right);
    void setSpeed(float speed);
    void setPosition(float x, float y);
    void setDirection(int direction);
    void setImage(const std::string& image_name); 
    // Tipos antikeimenou 
    std::string m_type;
    std::string getType() const { return m_type; }
};


