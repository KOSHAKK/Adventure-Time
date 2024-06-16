#include "../Resources/ResourceManager.hpp"
#include "../Physics/PhysicsEngine.hpp"
#include "../Game/CopperBlock.hpp"
#include "../System/KeyState.hpp"
#include "../Render/Sprite.hpp"
#include "../System/Keys.hpp"
#include "MyceliumBlock.hpp"
#include "../Game/Border.hpp"
#include <glm/vec2.hpp>
#include "Level_1.hpp"
#include "../Game/Fruit.hpp"

#include <iostream>
#include <array>

void Level_1::init()
{
    BLOCK_SIZE = 64;

    std::vector<std::string> terrain_sub_textures_names{
        "left_top_border",
        "top_border",
        "right_top_border",
        "left_top_sub_border",
        "right_top_sub_border",
        "NONE1",
        "mycelium_block_1",
        "mycelium_block_2",
        "mycelium_block_3",
        "mycelium_dirt_1",
        "mycelium_dirt_2",
        "NONE2",
        "coper3x1_1",
        "coper3x1_2",
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
        "right_border",
        "left_bottom_sub_border",
        "right_bottom_sub_border",
        "mycelium_dirt_3",
        "mycelium_dirt_4",
        "mycelium_dirt_5",
        "mycelium_dirt_6",
        "mycelium_dirt_7",
        "NONE5",
        "coper2x2_1",
        "coper1x1_1", // fix
        "coper2x2_2",
        "NONE6",
        "coper1x3_2",
        "gold2x2_1",
        "gold1x1",
        "gold2x2_2",
        "gold1x3_2",
        "Xdddd",
        "Xdddd",
        "left_bottom_border",
        "bottom_border",
        "right_bottom_border",
        "NONE7",
        "NONE8",
        "NONE9",
        "mycelium_dirt_8",
        "mycelium_dirt_9",
        "mycelium_dirt_10",
        "NONE10",
        "NONE11",
        "NONE12",
        "NONE13",
        "coper2x2_3",
        "coper2x2_4",
        "coper1x3_3",
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


    std::vector<std::string> apple_sub_textures_names{
        "apple1",
        "apple2",
        "apple3",
        "apple4",
        "apple5",
        "apple6",
        "apple7",
        "apple8",
        "apple9",
        "apple10",
        "apple11",
        "apple12",
        "apple13",
        "apple14",
        "apple15",
        "apple16",
        "apple17",
    };
    ResourceManager::load_texture_atlas("fruit_apple_atlas", "res/Textures/Fruits/Apple.png", apple_sub_textures_names, 32, 32);


    std::vector<std::string> collected_sub_textures_names{
        "collected1",
        "collected2",
        "collected3",
        "collected4",
        "collected5",
        "collected6",
    };
    ResourceManager::load_texture_atlas("fruit_collected_atlas", "res/Textures/Fruits/Collected.png", collected_sub_textures_names, 32, 32);




    m_player = std::make_unique<NinjaFrog>(glm::vec2(100, 500), glm::vec2(100, 100), 0.25f);
    PhysicsEngine::addDynamicGameObject(m_player);
    PhysicsEngine::set_current_player(m_player);

    unsigned int offsetX = 0;
    int offsetY = get_height() - 64;
    
    for (size_t i = 0; i < m_map.size(); i++)
    {
        offsetY -= BLOCK_SIZE;
        for (size_t j = 0; j < m_map[i].size(); j++)
        {
            m_game_objects.emplace_back(get_object_from_decsription(m_map[i][j], glm::vec2(static_cast<float>(BLOCK_SIZE)), glm::vec2(offsetX, offsetY)));
            if (m_game_objects.back())
            {
                PhysicsEngine::addDynamicGameObject(m_game_objects.back());
               // m_game_objects.back()->set_pos(glm::vec2(offsetX, offsetY));
                //m_game_objects.back()->set_size(glm::vec2(BLOCK_SIZE, BLOCK_SIZE));
            }
            offsetX += BLOCK_SIZE;
            if (offsetX >= get_width())
            {
                offsetX = 0;
            }
        }
    }





    ResourceManager::load_texture("background_yellow", "res/Background/Gray.png");

    m_background = ResourceManager::load_sprite("backgound_yellow_sprite", "default_shader", "background_yellow", 128, 128);
    m_background->set_position({ 150, 150 });

} 

void Level_1::render()
{
    for (unsigned int i = 0; i < m_width / 128; i++)
    {
        for (unsigned int j = 0; j < m_height / 128; j++)
        {
            m_background->set_position(glm::vec2(i * 128, (j * 128) + m_background_pos));
            m_background->render();

        }
    }

    m_background->render();
    ILevel::render();
    if (m_player)
    {
        m_player->render();
    }
}

void Level_1::update(const uint64_t delta)
{
    if (m_background_pos <= -128.f) 
    {
        m_background_pos = 0.f;
    }
    m_background_pos -= 0.027f * delta;




    ILevel::update(delta);
    if (m_player)
    {
        m_player->update(delta);

        if (KeyState::get_key_state(Keys::KEY_SPACE) && m_player->get_jump_power() == 0.f && !m_player->is_fall() && has_object_down(m_player->get_pos() + 36.f, (m_player->get_pos() + m_player->get_size()) - 20.f))
        {
            m_player->set_jump(true);
            m_player->set_jump_power(m_player->get_max_jump_power());
        }
        if (KeyState::get_key_state(Keys::KEY_S) || KeyState::get_key_state(Keys::KEY_A) || KeyState::get_key_state(Keys::KEY_D) || KeyState::get_key_state(Keys::KEY_R))
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

            if (KeyState::get_key_state(Keys::KEY_R))
            {
                m_player->set_pos(glm::vec2(100, 500));
            }
        }
        else
        {
            m_player->get_velocity() = 0.f;
        }
    }
}



std::shared_ptr<IGameObject> Level_1::get_object_from_decsription(const char description, const glm::vec2& scale, const glm::vec2& pos)
{
    switch (description)
    {
    case 'Q':
        return std::make_shared<MyceliumBlock>(MyceliumBlock::EType::MYCELIUM_BLOCK_1, pos, scale);
    case 'W':
        return std::make_shared<MyceliumBlock>(MyceliumBlock::EType::MYCELIUM_BLOCK_2, pos, scale);
    case 'E':
        return std::make_shared<MyceliumBlock>(MyceliumBlock::EType::MYCELIUM_BLOCK_3, pos, scale);
    case 'Z':
        return std::make_shared<MyceliumBlock>(MyceliumBlock::EType::MYCELIUM_DIRT_1, pos, scale);
    case 'X':
        return std::make_shared<MyceliumBlock>(MyceliumBlock::EType::MYCELIUM_DIRT_2, pos, scale);
    case 'B':
        return std::make_shared<Border>(Border::EType::LEFT_TOP_BORDER, pos, scale, 0.f);
    case 'N':
        return std::make_shared<Border>(Border::EType::RIGHT_TOP_BORDER, pos, scale, 0.f);
    case 'M':
        return std::make_shared<Border>(Border::EType::RIGHT_BORDER, pos, scale, 0.f);
    case 'L':
        return std::make_shared<Border>(Border::EType::LEFT_BORDER, pos, scale, 0.f);
    case 'P':
        return std::make_shared<Border>(Border::EType::TOP_BORDER, pos, scale, 0.f);
    case 'I':
        return std::make_shared<Border>(Border::EType::RIGHT_BOTTOM_BORDER, pos, scale, 0.f);
    case 'U':
        return std::make_shared<Border>(Border::EType::LEFT_BOTTOM_BORDER, pos, scale, 0.f);
    case 'Y':
        return std::make_shared<Border>(Border::EType::BOTTOM_BORDER, pos, scale, 0.f);
    case 'J':
        return std::make_shared<Border>(Border::EType::LEFT_TOP_SUB_BORDER, pos, scale, 0.f);
    case 'T':
        return std::make_shared<Border>(Border::EType::RIGHT_TOP_SUB_BORDER, pos, scale, 0.f);
    case 'G':
        return std::make_shared<Border>(Border::EType::LEFT_BOTTOM_SUB_BORDER, pos, scale, 0.f);
    case 'F':
        return std::make_shared<Border>(Border::EType::RIGHT_BOTTOM_SUB_BORDER, pos, scale, 0.f);
    case 'A':
        return std::make_shared<CopperBlock>(CopperBlock::EType::COPPER_BLOCK_1x3_1, pos, scale, 0.f);
    case 'S':
        return std::make_shared<CopperBlock>(CopperBlock::EType::COPPER_BLOCK_1x3_2, pos, scale, 0.f);
    case 'D':
        return std::make_shared<CopperBlock>(CopperBlock::EType::COPPER_BLOCK_1x3_3, pos, scale, 0.f);
    case 'V':
        return std::make_shared<CopperBlock>(CopperBlock::EType::COPPER_BLOCK_3x1_1, pos, scale, 0.f);
    case 'C':
        return std::make_shared<CopperBlock>(CopperBlock::EType::COPPER_BLOCK_3x1_2, pos, scale, 0.f);
    case 'H':
        return std::make_shared<CopperBlock>(CopperBlock::EType::COPPER_BLOCK_3x1_3, pos, scale, 0.f);
    case 'R':
        return std::make_shared<CopperBlock>(CopperBlock::EType::COPPER_BLOCK_1x1_1, pos, scale, 0.f);
    case 'K':
        return std::make_shared<Fruit>(Fruit::EType::Apple, pos, scale, 0.f);
    default:
        return nullptr;
    }
}
