#pragma once
#include <array>
#include <memory>
#include <glm/vec2.hpp>
#include "MyceliumBlock.hpp"
#include "ILevel.hpp"
#include "NinjaFrog.hpp"


class Game
{
public:

	void init(const glm::vec2& window_size);

	void set_key(const int key, const int action);
	void update(const uint64_t delta);
	void render() const;

private:
	std::array<bool, 349> m_keys;
	std::unique_ptr<glm::vec2> m_window_size;

	std::unique_ptr<ILevel> level_1;


};