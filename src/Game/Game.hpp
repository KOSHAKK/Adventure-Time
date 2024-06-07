#pragma once
#include <array>
#include <memory>
#include <glm/vec2.hpp>
#include "MyceliumBlock.hpp"
#include "ILevel.hpp"
#include "NinjaFrog.hpp"
#include "../Render/ShaderProgram.hpp"

class Game
{
public:

	void init(const glm::uvec2& window_size);

	void update(const uint64_t delta);
	void render() const;

	void set_window_size(const glm::uvec2& windowSize);
	void update_viewport();

	void set_viewport(const unsigned int width, const unsigned int height, const unsigned int leftOffset, const unsigned int bottomOffset);

	unsigned int get_fps() const;

	unsigned int get_current_width() const;
	unsigned int get_current_height() const;


private:
	glm::uvec2 m_window_size;
	std::shared_ptr<Render::ShaderProgram> m_pShaderProgram;

	std::shared_ptr<ILevel> level_1;
	unsigned int m_fps = 0;

	unsigned int frame_counter = 0;
	uint64_t timer = 0.f;

};