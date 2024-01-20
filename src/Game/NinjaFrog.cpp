#include "NinjaFrog.hpp"
#include "../Render/AnimatedSprite.hpp"
#include "../Render/Sprite.hpp"
#include "../Resources/ResourceManager.hpp"
#include <vector>
#include <iostream>

NinjaFrog::NinjaFrog(const glm::vec2& pos, const glm::vec2& scale, const float max_velocity, const float rotate)
    : m_MAX_SPEED(max_velocity)
{


    m_object_type = IGameObject::EObjectType::PLAYER;
	static int counter = 0;
	counter++;
	m_sprites[static_cast<size_t>(EState::IDLE)] = ResourceManager::load_animated_sprite("NinjaFrog" + std::to_string(counter),
		"ninja_frog_idle_atlas", "default_shader", static_cast<const unsigned int>(scale.x), static_cast<const unsigned int>(scale.y), "ninja_frog_idle1");


	std::vector<std::pair<std::string, uint64_t>> idle_states = {
        std::make_pair("ninja_frog_idle1", 50),
        std::make_pair("ninja_frog_idle2", 50),
        std::make_pair("ninja_frog_idle3", 50),
        std::make_pair("ninja_frog_idle4", 50),
        std::make_pair("ninja_frog_idle5", 50),
        std::make_pair("ninja_frog_idle6", 50),
        std::make_pair("ninja_frog_idle7", 50),
        std::make_pair("ninja_frog_idle8", 50),
        std::make_pair("ninja_frog_idle9", 50),
        std::make_pair("ninja_frog_idle10", 50),
        std::make_pair("ninja_frog_idle11", 50),
	};
	m_sprites[static_cast<size_t>(EState::IDLE)]->insertState("idle_state", std::move(idle_states));
    m_sprites[static_cast<size_t>(EState::IDLE)]->setState("idle_state");
    m_sprites[static_cast<size_t>(EState::IDLE)]->set_position(pos);
    m_sprites[static_cast<size_t>(EState::IDLE)]->set_rotate(rotate);

    m_sprites[static_cast<size_t>(EState::RUN)] = ResourceManager::load_animated_sprite("NinjaFrog" + std::to_string(counter),
        "ninja_frog_run_atlas", "default_shader", static_cast<const unsigned int>(scale.x), static_cast<const unsigned int>(scale.y), "ninja_frog_run1");
    std::vector<std::pair<std::string, uint64_t>> run_states = {
        std::make_pair("ninja_frog_run1", 50),
        std::make_pair("ninja_frog_run2", 50),
        std::make_pair("ninja_frog_run3", 50),
        std::make_pair("ninja_frog_run4", 50),
        std::make_pair("ninja_frog_run5", 50),
        std::make_pair("ninja_frog_run6", 50),
        std::make_pair("ninja_frog_run7", 50),
        std::make_pair("ninja_frog_run8", 50),
        std::make_pair("ninja_frog_run9", 50),
        std::make_pair("ninja_frog_run10", 50),
        std::make_pair("ninja_frog_run11", 50),
        std::make_pair("ninja_frog_run12", 50),
    };
    m_sprites[static_cast<size_t>(EState::RUN)]->insertState("run_state", std::move(run_states));
    m_sprites[static_cast<size_t>(EState::RUN)]->setState("run_state");
    m_sprites[static_cast<size_t>(EState::RUN)]->set_position(pos);
    m_sprites[static_cast<size_t>(EState::RUN)]->set_rotate(rotate);


    m_sprites[static_cast<size_t>(EState::JUMP)] = ResourceManager::load_animated_sprite("NinjaFrog" + std::to_string(counter),
        "ninja_frog_jump_atlas", "default_shader", static_cast<const unsigned int>(scale.x), static_cast<const unsigned int>(scale.y), "ninja_frog_jump1");
    std::vector<std::pair<std::string, uint64_t>> jump_states = {
       std::make_pair("ninja_frog_jump1", 50),
    };
    m_sprites[static_cast<size_t>(EState::JUMP)]->insertState("jump_state", jump_states);
    m_sprites[static_cast<size_t>(EState::JUMP)]->setState("jump_state");
    m_sprites[static_cast<size_t>(EState::JUMP)]->set_position(pos);
    m_sprites[static_cast<size_t>(EState::JUMP)]->set_rotate(rotate);


    m_sprites[static_cast<size_t>(EState::FALL)] = ResourceManager::load_animated_sprite("NinjaFrog" + std::to_string(counter),
        "ninja_frog_fall_atlas", "default_shader", static_cast<const unsigned int>(scale.x), static_cast<const unsigned int>(scale.y), "ninja_frog_fall1");
    std::vector<std::pair<std::string, uint64_t>> fall_states = {
       std::make_pair("ninja_frog_fall1", 50),
    };
    m_sprites[static_cast<size_t>(EState::FALL)]->insertState("fall_state", fall_states);
    m_sprites[static_cast<size_t>(EState::FALL)]->setState("fall_state");
    m_sprites[static_cast<size_t>(EState::FALL)]->set_position(pos);
    m_sprites[static_cast<size_t>(EState::FALL)]->set_rotate(rotate);

    m_colliderds.emplace_back(PhysicsEngine::AABB(glm::vec2(20.f, 3.f), get_size() - 20.f));
}

void NinjaFrog::update(const uint64_t delta)
{
    m_sprites[static_cast<size_t>(m_state)]->update(delta);

    if (m_velocity > 0.f)
    {
        m_state = EState::RUN;
    }
    else
    {
        m_state = EState::IDLE;
    }

    if (m_is_jump)
    {
        m_state = EState::JUMP;
    }
    if (m_is_fall)
    {
        m_state = EState::FALL;
    }
}

void NinjaFrog::render() const
{
    m_sprites[static_cast<size_t>(m_state)]->render(!m_is_right);
}

void NinjaFrog::set_orientation(const bool is_left)
{
	m_is_right = is_left;
}


void NinjaFrog::set_state(const EState state)
{
	m_state = state;
}

glm::vec2 NinjaFrog::get_pos() const
{
    return m_sprites[static_cast<size_t>(m_state)]->get_position();
}

glm::vec2 NinjaFrog::get_size() const
{
    return m_sprites[static_cast<size_t>(m_state)]->get_scale();
}

float NinjaFrog::get_rotation() const
{
    return m_sprites[static_cast<size_t>(m_state)]->get_rotate();
}

void NinjaFrog::set_rotation(const float rotation)
{
    for (auto& sprite : m_sprites)
    {
        if (sprite)
        {
            sprite->set_rotate(rotation);
        }
    }
}

void NinjaFrog::set_size(const glm::vec2& size)
{
    for (auto& sprite : m_sprites)
    {
        if (sprite)
        {
            sprite->set_scale(size);
        }
    }
}

void NinjaFrog::set_pos(const glm::vec2& position)
{
    for (auto& sprite : m_sprites)
    {
        if (sprite)
        {
            sprite->set_position(position);

        }
    }

}
