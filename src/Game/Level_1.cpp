#include "Level_1.hpp"
#include "../Resources/ResourceManager.hpp"
#include "MyceliumBlock.hpp"

void Level_1::init()
{
    std::vector<std::string> terrain_sub_textures_names{
    "empty3x1_1",
    "empty3x1_2",
    "mycelium_block3x1"
    };
    ResourceManager::load_texture_atlas("terrain_atlas", "res/Textures/Terrain/Terrain (16x16).png", terrain_sub_textures_names, 48, 16);



    m_static_game_objects.emplace_back(std::make_shared<MyceliumBlock>(glm::vec2(100.f, 100.f), glm::vec2(64*3, 64)));
}
