#pragma once
#include <vector>
#include <string>
#include <glm/vec2.hpp>
#include <memory>

namespace Render
{
	class Sprite;

	class AnimatedSprite
	{
	public:
		AnimatedSprite(const std::string& atlas_name,
					   const std::vector<std::string>& sub_textures_name,
					   const std::string& shader_program_name,
					   const unsigned int delay_ms, 
					   const glm::vec2& position, 
					   const glm::vec2& size, 
					   const float rotate = 0.f);

		void render() const;

		void update(const unsigned int delta_time);

		void set_position(const glm::vec2& pos);

	private:
		unsigned int m_current_sprite = 0;
		std::vector<std::shared_ptr<Sprite>> m_sprites;

		unsigned int m_elapsed_time = 0;

		unsigned int m_delay;
		glm::vec2 m_position;
		glm::vec2 m_size;
		float m_rotate;
	};
	
}