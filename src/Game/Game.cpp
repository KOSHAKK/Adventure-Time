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

}

void Game::set_key(const int key, const int action)
{
	m_keys[key] = action;
}

void Game::update(const uint64_t delta)
{
    level_1->update(delta);
}

void Game::render() const
{
    level_1->render();
}
