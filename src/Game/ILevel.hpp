#pragma once
#include <vector>
#include <memory>
#include <array>
#include <glm/vec2.hpp>

class IGameObject;

class ILevel
{
public:
	ILevel(const unsigned int BLOCK_SIZE, const unsigned int width, const unsigned int height);
	void virtual init() = 0;
	void virtual render();
	void virtual update(const uint64_t delta);
	unsigned int get_width() const;
	unsigned int get_height() const;

	const std::vector<std::shared_ptr<IGameObject>>& get_object_in_area(const glm::vec2& bottom_left, const glm::vec2& top_right) const;

	unsigned int get_block_size() const;

protected:
	bool m_is_finish = false;
	unsigned int BLOCK_SIZE;
	unsigned int m_width;
	unsigned int m_height;
	std::shared_ptr<std::array<bool, 349>> m_keys;

	std::vector<std::shared_ptr<IGameObject>> m_game_objects;
};