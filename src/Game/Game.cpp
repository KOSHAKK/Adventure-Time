#include "Game.hpp"
#include <iostream>
#include "Level_1.hpp"
#include <glm/mat4x4.hpp>
#include "../System/Keys.hpp"
#include "../Render/Sprite.hpp"
#include "../System/KeyState.hpp"
#include "../Render/Texture2D.hpp"
#include "../Render/ShaderProgram.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "../Physics/PhysicsEngine.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "../Render/AnimatedSprite.hpp"
#include "../Resources/ResourceManager.hpp"

void Game::init(const glm::uvec2& window_size)
{
    m_window_size = window_size;
    m_pShaderProgram = ResourceManager::load_shader_program("default_shader", "res/Shaders/vs.vert", "res/Shaders/fs.frag");


    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_window_size.x), 0.f, static_cast<float>(m_window_size.y), -100.f, 100.f);

    m_pShaderProgram->use();
    m_pShaderProgram->set_matrix4("projection", projectionMatrix);

    

    level_1 = std::make_shared<Level_1>(64, 64 * 3 * 6, 64 * 3 * 4);
    level_1->init();
    PhysicsEngine::set_current_level(level_1);

}

void Game::update(const uint64_t delta)
{
    frame_counter++;
    timer += delta;
    if (timer >= 1000)
    {
        timer = 0.f;
        m_fps = frame_counter;
        frame_counter = 0;
    }


    level_1->update(delta);
}

void Game::render() const
{
    level_1->render();
}

void Game::set_window_size(const glm::uvec2& windowSize)
{
    m_window_size = windowSize;
}

void Game::update_viewport()
{
    const float level_aspect_ratio = static_cast<float>(get_current_width()) / get_current_height();
    unsigned int viewPortWidth = m_window_size.x;
    unsigned int viewPortHeight = m_window_size.y;
    unsigned int viewPortLeftOffset = 0;
    unsigned int viewPortBottomOffset = 0;

    if (static_cast<float>(m_window_size.x) / m_window_size.y > level_aspect_ratio)
    {
        viewPortWidth = static_cast<unsigned int>(m_window_size.y * level_aspect_ratio);
        viewPortLeftOffset = (m_window_size.x - viewPortWidth) / 2;
    }
    else
    {
        viewPortHeight = static_cast<unsigned int>(m_window_size.x / level_aspect_ratio);
        viewPortBottomOffset = (m_window_size.y - viewPortHeight) / 2;
    }

    set_viewport(viewPortWidth, viewPortHeight, viewPortLeftOffset, viewPortBottomOffset);

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(get_current_width()), 0.f, static_cast<float>(get_current_height()), -100.f, 100.f);
    m_pShaderProgram->set_matrix4("projection", projectionMatrix);
}

void Game::set_viewport(const unsigned int width, const unsigned int height, const unsigned int leftOffset, const unsigned int bottomOffset)
{
    glViewport(leftOffset, bottomOffset, width, height);
}

unsigned int Game::get_fps() const
{
    return m_fps;
}

unsigned int Game::get_current_width() const
{
    return level_1->get_width();
}

unsigned int Game::get_current_height() const
{
    return level_1->get_height();
}
