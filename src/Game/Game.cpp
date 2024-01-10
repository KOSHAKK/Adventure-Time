#include "Game.hpp"
#include <iostream>
#include "Level_1.hpp"
#include <glm/mat4x4.hpp>
#include "../System/Keys.hpp"
#include "../Render/Sprite.hpp"
#include "../Render/Texture2D.hpp"
#include "../Render/ShaderProgram.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "../Render/AnimatedSprite.hpp"
#include "../Resources/ResourceManager.hpp"

void Game::init(const glm::vec2& window_size)
{
    m_window_size = std::make_unique<glm::vec2>(window_size);
    auto shader = ResourceManager::load_shader_program("default_shader", "res/Shaders/vs.vert", "res/Shaders/fs.frag");


    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_window_size->x), 0.f, static_cast<float>(m_window_size->y), -100.f, 100.f);

    shader->use();
    shader->set_matrix4("projection", projectionMatrix);




    level_1 = std::make_unique<Level_1>();
    level_1->init();



    std::vector<std::string> ninja_run_sub_textures_names{
        "Run1",
        "Run2",
        "Run3",
        "Run4",
        "Run5",
        "Run6",
        "Run7",
        "Run8",
        "Run9",
        "Run10",
        "Run11",
        "Run12",
    };


    ResourceManager::load_texture_atlas("atl", "res/Textures/Main Characters/Ninja Frog/Run (32x32).png", ninja_run_sub_textures_names, 32, 32);


    zxc = ResourceManager::load_animated_sprite("zxcqwe", "atl", "default_shader", 100, 100, "Run1");

    std::vector<std::pair<std::string, uint64_t>> state;
    state.emplace_back(std::make_pair<std::string, uint64_t>("Run1", 50));
    state.emplace_back(std::make_pair<std::string, uint64_t>("Run2", 50));
    state.emplace_back(std::make_pair<std::string, uint64_t>("Run3", 50));
    state.emplace_back(std::make_pair<std::string, uint64_t>("Run4", 50));
    state.emplace_back(std::make_pair<std::string, uint64_t>("Run5", 50));
    state.emplace_back(std::make_pair<std::string, uint64_t>("Run6", 50));
    state.emplace_back(std::make_pair<std::string, uint64_t>("Run7", 50));
    state.emplace_back(std::make_pair<std::string, uint64_t>("Run8", 50));
    state.emplace_back(std::make_pair<std::string, uint64_t>("Run9", 50));
    state.emplace_back(std::make_pair<std::string, uint64_t>("Run10", 50));
    state.emplace_back(std::make_pair<std::string, uint64_t>("Run11", 50));
    state.emplace_back(std::make_pair<std::string, uint64_t>("Run12", 50));



    zxc->insertState("run_state", state);
    zxc->setState("run_state");

    zxc->set_position(glm::vec2(300.f, 300.f));

}

void Game::set_key(const int key, const int action)
{
	m_keys[key] = action;
}

void Game::update(const uint64_t delta)
{
    level_1->update(delta);
    zxc->update(delta);
}

void Game::render() const
{
    level_1->render();
    zxc->render();
}
