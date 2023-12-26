#include "AnimatedSprite.hpp"
#include "Sprite.hpp"
#include "../Resources/ResourceManager.hpp"
#include <iostream>


namespace Render
{
	AnimatedSprite::AnimatedSprite(const std::string& atlas_name,
								   const std::vector<std::string>& sub_textures_name,
								   const std::string& shader_program_name,
								   const unsigned int delay_ms,
								   const glm::vec2& position,
								   const glm::vec2& size,
								   const float rotate)
		: m_delay(delay_ms),
		m_position(position),
		m_size(size),
		m_rotate(rotate)
	{
		//m_sprites.resize(sub_textures_name.size());

		for (const auto& curr_name : sub_textures_name)
		{
			auto sp = ResourceManager::load_sprite(curr_name, shader_program_name, atlas_name, m_size.x, m_size.y, curr_name);
			sp->set_position(m_position);
			sp->set_rotate(m_rotate);
			m_sprites.emplace_back(sp);
		}
	}

	void AnimatedSprite::render() const
	{
		m_sprites[m_current_sprite]->render();
	}
	void AnimatedSprite::update(const unsigned int delta_time)
	{
		if (m_elapsed_time >= m_delay)
		{
			m_elapsed_time = 0;
			m_current_sprite++;
		}

		if (m_current_sprite >= m_sprites.size() - 1)
		{
			m_current_sprite = 0;
		}

		std::cout << m_current_sprite << std::endl;
		m_elapsed_time += delta_time;
	}
	void AnimatedSprite::set_position(const glm::vec2& pos)
	{
		for (auto& curr : m_sprites)
		{
			curr->set_position(pos);
		}
	}
}