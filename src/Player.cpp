#include "include/Player.h"


Player::Player()
{
    pm_camera.position = (Vector3){ 2.0f, 2.0f, 2.0f };
    pm_camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    pm_camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    pm_camera.fovy = 30.0f;
    pm_camera.projection = CAMERA_PERSPECTIVE;

    SetCameraMode(pm_camera, CAMERA_FIRST_PERSON);
};

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

void Player::begin_mode3d() { BeginMode3D(pm_camera); }
void Player::update_cam() { UpdateCamera(&pm_camera); }

void Player::update_player()
{
    pm_position.x = pm_camera.position.x;
    pm_position.z = pm_camera.position.z; 
}