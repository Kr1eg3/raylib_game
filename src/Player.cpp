#include "include/Player.h"


Player::Player() {};
Player::~Player() {};

void Player::set_player_posX(float x) { pm_position.x = x; }
void Player::set_player_posY(float y) { pm_position.y = y; }
void Player::set_player_posZ(float z) { pm_position.z = z; };
void Player::set_player_hp(int val) { pm_health_points = val; }
void Player::set_player_pos(Vector3 vec3) { pm_position = vec3; }

int Player::get_player_hp() { return pm_health_points; }
Vector3 Player::get_player_pos() { return pm_position; }
float Player::get_player_posX() { return pm_position.x; }
float Player::get_player_posY() { return pm_position.y; }
float Player::get_player_posZ() { return pm_position.z; }

void Player::update_player()
{
    
}