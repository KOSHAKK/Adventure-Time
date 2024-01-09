#pragma once
#include <array>
#include <memory>
#include <glm/vec2.hpp>

namespace Render
{
	class AnimatedSprite;
};

class Game
{
public:

	void init(const glm::vec2& window_size);

	void set_key(const int key, const int action);
	void update(const uint64_t delta);

private:
	std::array<bool, 349> m_keys;
	std::unique_ptr<glm::vec2> m_window_size;




	//-------------------------
	std::shared_ptr<Render::AnimatedSprite> animatedSprite;
	glm::vec2 pos{ 200.f,200.f };
};