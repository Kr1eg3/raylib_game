#pragma once

#include <vector>
#include "raylib.h"

struct Static_object
{
    Model model;
    Texture2D texture;
    Vector3 position {};
    float scale {};
};

class World
{
private:
    std::vector<Static_object> static_objects;


public:
    World();

    void push_static_object(Static_object);
    void apply_textures_for_static_objects();
    void draw_static_objects();
};
