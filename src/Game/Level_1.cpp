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

    std::vector<std::string> ninja_run_sub_textures_names{
        "ninja_frog_run1",
        "ninja_frog_run2",
        "ninja_frog_run3",
        "ninja_frog_run4",
        "ninja_frog_run5",
        "ninja_frog_run6",
        "ninja_frog_run7",
        "ninja_frog_run8",
        "ninja_frog_run9",
        "ninja_frog_run10",
        "ninja_frog_run11",
        "ninja_frog_run12"
    };
    ResourceManager::load_texture_atlas("ninja_frog_run_atlas", "res/Textures/Main Characters/Ninja Frog/Run (32x32).png", ninja_run_sub_textures_names, 32, 32);

    std::vector<std::string> ninja_idle_sub_textures_names{
        "ninja_frog_idle1",
        "ninja_frog_idle2",
        "ninja_frog_idle3",
        "ninja_frog_idle4",
        "ninja_frog_idle5",
        "ninja_frog_idle6",
        "ninja_frog_idle7",
        "ninja_frog_idle8",
        "ninja_frog_idle9",
        "ninja_frog_idle10",
        "ninja_frog_idle11",
    };
    ResourceManager::load_texture_atlas("ninja_frog_idle_atlas", "res/Textures/Main Characters/Ninja Frog/Idle (32x32).png", ninja_idle_sub_textures_names, 32, 32);

    m_player = std::make_unique<NinjaFrog>(glm::vec2(300, 300), glm::vec2(100, 100));


    m_static_game_objects.emplace_back(std::make_shared<MyceliumBlock>(glm::vec2(100.f, 100.f), glm::vec2(64*3, 64)));
}

void Level_1::render()
{
    ILevel::render();
    if (m_player)
    {
        m_player->render();
    }
}

void Level_1::update(const uint64_t delta)
{
    ILevel::update(delta);
    if (m_player)
    {
        m_player->update(delta);
    }
}
