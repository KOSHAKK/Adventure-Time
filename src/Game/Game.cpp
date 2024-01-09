#include "Game.hpp"
#include "../System/Keys.hpp"
#include <iostream>
#include "../Resources/ResourceManager.hpp"
#include "../Render/ShaderProgram.hpp"
#include "../Render/Texture2D.hpp"
#include "../Render/Sprite.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Render/AnimatedSprite.hpp"


void Game::init(const glm::vec2& window_size)
{
    m_window_size = std::make_unique<glm::vec2>(window_size);

    std::vector<std::string> sub_textures_names{
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "10",
        "11",
        "12",
        "13",
        "14",
        "15",
        "16",
        "17",
        "18",
        "19",
        "20",
        "21",
        "22",
        "23",
        "24"
    };

    auto shader = ResourceManager::load_shader_program("default_shader", "res/Shaders/vs.vert", "res/Shaders/fs.frag");

    auto atlas = ResourceManager::load_texture_atlas("defaultAtlas", "res/Textures/Main Characters/Virtual Guy/DinoSprites - doux.png", sub_textures_names, 24, 24);

    ResourceManager::load_sprite("NewSpite", "default_shader", "defaultAtlas", 78, 58, "1");



    animatedSprite = ResourceManager::load_animated_sprite("zxc1", "defaultAtlas", "default_shader", 200, 200, "1");
    animatedSprite->set_position(glm::vec2(300, 300));
    std::vector<std::pair<std::string, uint64_t>> state;
    state.emplace_back(std::make_pair<std::string, uint64_t>("5", 100));
    state.emplace_back(std::make_pair<std::string, uint64_t>("6", 100));
    state.emplace_back(std::make_pair<std::string, uint64_t>("7", 100));
    state.emplace_back(std::make_pair<std::string, uint64_t>("8", 100));
    state.emplace_back(std::make_pair<std::string, uint64_t>("9", 100));
    state.emplace_back(std::make_pair<std::string, uint64_t>("10", 100));
    state.emplace_back(std::make_pair<std::string, uint64_t>("11", 100));


    animatedSprite->insertState("st", state);
    animatedSprite->setState("st");



    /* Loop until the user closes the window */

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_window_size->x), 0.f, static_cast<float>(m_window_size->y), -100.f, 100.f);

    shader->use();
    shader->set_matrix4("projection", projectionMatrix);
}

void Game::set_key(const int key, const int action)
{
	m_keys[key] = action;
}

void Game::update(const uint64_t delta)
{
    if (m_keys[static_cast<size_t>(Keys::GLFW_KEY_W)]) {
        pos.y += 1.f;
    }
    else if (m_keys[static_cast<size_t>(Keys::GLFW_KEY_S)]) {
        pos.y -= 1.f;
    }

    if (m_keys[static_cast<size_t>(Keys::GLFW_KEY_D)]) {
        pos.x += 1.f;
    }
    else if (m_keys[static_cast<size_t>(Keys::GLFW_KEY_A)]) {
        pos.x -= 1.f;
    }

    animatedSprite->set_position(pos);
    animatedSprite->update(delta);
    animatedSprite->render();
    
}
