#include "include/World.h"


World::World() {};


void World::push_static_object(Static_object obj) { static_objects.push_back(obj); }

void World::apply_textures_for_static_objects()
{
    for (auto stat_obj: static_objects)
    {
        stat_obj.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = stat_obj.texture;
    }
}

void World::draw_static_objects()
{
    for (auto stat_obj: static_objects)
        DrawModel(stat_obj.model, stat_obj.position, stat_obj.scale, WHITE);
}

