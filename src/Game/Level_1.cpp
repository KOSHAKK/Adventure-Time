#include "Level_1.hpp"
#include "../Resources/ResourceManager.hpp"
#include "MyceliumBlock.hpp"
#include "../Physics/PhysicsEngine.hpp"
#include "../System/Keys.hpp"
#include "../System/KeyState.hpp"
#include <iostream>
#include <array>
#include <glm/vec2.hpp>
#include "../Game/Border.hpp"

void Level_1::init()
{
    BLOCK_SIZE = 64;

    std::vector<std::string> terrain_sub_textures_names{
        "left_top_border",
        "top_border",
        "right_top_border",
        "empty1",
        "empty2",
        "NONE1",
        "mycelium_block_1",
        "mycelium_block_2",
        "mycelium_block_3",
        "mycelium_dirt_1",
        "mycelium_dirt_2",
        "NONE2",
        "coper3x1_1",
        "coper3x1_1",
        "coper3x1_3",
        "coper1x3_1",
        "NONE3",
        "gold3x1_1",
        "gold3x1_2",
        "gold3x1_3",
        "gold1x3_1",
        "border_empty",
        "left_border",
        "empty4",
        "right_border_1",
        "right_border",
        "mycelium_dirt_3",
        "mycelium_dirt_4",
        "mycelium_dirt_5",
        "mycelium_dirt_6",
        "mycelium_dirt_7",
        "NONE5",
        "coper1x1",
        "coper2x2_1",
        "coper2x2_2",
        "NONE6",
        "gold1x1",
        "gold2x2_1",
        "gold2x2_2",
        "gold1x3_2",
        "2",
        "Xdddd",
        "1",
        "3",
        "left_bottom_border",
        "bottom_border",
        "right_bottom_border",


    };
    ResourceManager::load_texture_atlas("terrain_atlas", "res/Textures/Terrain/Terrain (16x16).png", terrain_sub_textures_names, 16, 16);

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

    std::vector<std::string> ninja_jump_sub_textures_names{
        "ninja_frog_jump1",
    };
    ResourceManager::load_texture_atlas("ninja_frog_jump_atlas", "res/Textures/Main Characters/Ninja Frog/Jump (32x32).png", ninja_jump_sub_textures_names, 32, 32);

    std::vector<std::string> ninja_fall_sub_textures_names{
    "ninja_frog_fall1",
    };
    ResourceManager::load_texture_atlas("ninja_frog_fall_atlas", "res/Textures/Main Characters/Ninja Frog/Fall (32x32).png", ninja_fall_sub_textures_names, 32, 32);








    m_player = std::make_unique<NinjaFrog>(glm::vec2(300, 70), glm::vec2(100, 100), 0.25f);
    PhysicsEngine::addDynamicGameObject(m_player);

    unsigned int offsetX = 0;
    int offsetY = get_height() - 64;
    
    for (size_t i = 0; i < m_map.size(); i++)
    {
        offsetY -= BLOCK_SIZE;
        for (size_t j = 0; j < m_map[i].size(); j++)
        {
            m_game_objects.emplace_back(get_object_from_decsription(m_map[i][j], glm::vec2(BLOCK_SIZE)));
            if (m_game_objects.back())
            {
                PhysicsEngine::addDynamicGameObject(m_game_objects.back());
                m_game_objects.back()->set_pos(glm::vec2(offsetX, offsetY));
                m_game_objects.back()->set_size(glm::vec2(BLOCK_SIZE, BLOCK_SIZE));
            }
            offsetX += BLOCK_SIZE;
            if (offsetX >= get_width())
            {
                offsetX = 0;
            }
        }
    }
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

        if (KeyState::get_key_state(Keys::KEY_SPACE) && m_player->get_jump_power() == 0.f && !m_player->is_fall() && has_object_down(m_player->get_pos() + 36.f, (m_player->get_pos() + m_player->get_size()) - 20.f))
        {
            m_player->set_jump(true);
            m_player->set_jump_power(m_player->get_max_jump_power());
        }
        if (KeyState::get_key_state(Keys::KEY_S) || KeyState::get_key_state(Keys::KEY_A) || KeyState::get_key_state(Keys::KEY_D))
        {
            if (KeyState::get_key_state(Keys::KEY_A))
            {
                m_player->get_velocity() = m_player->get_max_velocity();
                m_player->set_orientation(false);
            }
            else if (KeyState::get_key_state(Keys::KEY_D))
            {
                m_player->get_velocity() = m_player->get_max_velocity();
                m_player->set_orientation(true);
            }
        }
        else
        {
            m_player->get_velocity() = 0.f;
        }
    }
}



std::shared_ptr<IGameObject> Level_1::get_object_from_decsription(const char description, const glm::vec2& scale)
{
    switch (description)
    {
    case 'Q':
        return std::make_shared<MyceliumBlock>(MyceliumBlock::EType::MYCELIUM_BLOCK_1, glm::vec2(0.f), scale);
    case 'W':
        return std::make_shared<MyceliumBlock>(MyceliumBlock::EType::MYCELIUM_BLOCK_2, glm::vec2(0.f), scale);
    case 'E':
        return std::make_shared<MyceliumBlock>(MyceliumBlock::EType::MYCELIUM_BLOCK_3, glm::vec2(0.f), scale);
    case 'Z':
        return std::make_shared<MyceliumBlock>(MyceliumBlock::EType::MYCELIUM_DIRT_1, glm::vec2(0.f), scale);
    case 'X':
        return std::make_shared<MyceliumBlock>(MyceliumBlock::EType::MYCELIUM_DIRT_2, glm::vec2(0.f), scale);
    case 'B':
        return std::make_shared<Border>(Border::EType::LEFT_TOP_BORDER, glm::vec2(0.f), scale, 0.f);
    case 'N':
        return std::make_shared<Border>(Border::EType::RIGHT_TOP_BORDER, glm::vec2(0.f), scale, 0.f);
    case 'M':
        return std::make_shared<Border>(Border::EType::RIGHT_BORDER, glm::vec2(0.f), scale, 0.f);
    case 'L':
        return std::make_shared<Border>(Border::EType::LEFT_BORDER, glm::vec2(0.f), scale, 0.f);
    case 'P':
        return std::make_shared<Border>(Border::EType::TOP_BORDER, glm::vec2(0.f), scale, 0.f);
    case 'I':
        return std::make_shared<Border>(Border::EType::RIGHT_BOTTOM_BORDER, glm::vec2(0.f), scale, 0.f);
    case 'U':
        return std::make_shared<Border>(Border::EType::LEFT_BOTTOM_BORDER, glm::vec2(0.f), scale, 0.f);
    case 'Y':
        return std::make_shared<Border>(Border::EType::BOTTOM_BORDER, glm::vec2(0.f), scale, 0.f);
    default:
        return nullptr;
    }
}
