#pragma once

#include <vector>
#include "raylib.h"

class Player
{
private:
    Camera pm_camera; 
    Vector3 pm_position;
    int pm_health_points;
public:
    Player();
    ~Player();

    void set_player_hp(int);
    void set_player_posX(float);
    void set_player_posY(float);
    void set_player_posZ(float);
    void set_player_pos(Vector3);

    int get_player_hp();
    float get_player_posX();
    float get_player_posY();
    float get_player_posZ();
    Vector3 get_player_pos();

    void update_player();

};