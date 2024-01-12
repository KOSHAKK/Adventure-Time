#include "ILevel.hpp"
#include "../Resources/ResourceManager.hpp"
#include "MyceliumBlock.hpp"
#include <glm/vec2.hpp>
#include <algorithm>

#include <iostream>

void ILevel::render()
{
	for (auto& obj : m_game_objects) {
		if (obj)
		{
			obj->render();
		}
	}
}

void ILevel::update(const uint64_t delta)
{
	for (auto& obj : m_game_objects) {
		if (obj)
		{
			obj->update(delta);
		}
	}
}

unsigned int ILevel::get_width() const
{
	return m_width;
}

unsigned int ILevel::get_height() const
{
	return m_height;
}

ILevel::ILevel(const unsigned int BLOCK_SIZE, const unsigned int width, const unsigned int height)
	: BLOCK_SIZE(BLOCK_SIZE),
	  m_width(width),
	  m_height(height)
{	
}

const std::vector<std::shared_ptr<IGameObject>>& ILevel::get_object_in_area(const glm::vec2& bottom_left, const glm::vec2& top_right) const
{
	std::vector<std::shared_ptr<IGameObject>> output;
	output.reserve(12);

	

	glm::vec2 bottom_left_converted(std::clamp(bottom_left.x - get_block_size(), 0.f, static_cast<float>(get_width())),
		std::clamp(get_height() - get_block_size() - bottom_left.y - get_block_size(), 0.f, static_cast<float>(get_height())));

	glm::vec2 top_right_coverted(std::clamp(top_right.x - get_block_size(), 0.f, static_cast<float>(get_width())),
		std::clamp(get_height() - get_block_size() - top_right.y - get_block_size(), 0.f, static_cast<float>(get_height())));


	

	std::cout << bottom_left_converted.x << " " << bottom_left_converted.y << std::endl;
	std::cout << top_right_coverted.x << " " << top_right_coverted.y << std::endl;
	std::cout << "-------------------------------------------------\n";

	return output;
}

unsigned int ILevel::get_block_size() const
{
	return BLOCK_SIZE;
}


