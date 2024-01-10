#pragma once
#include "IGameObject.hpp"

namespace Render
{
	class AnimatedSprite;
}

class NinjaFrog : public IGameObject
{
public:
	NinjaFrog(const glm::vec2& pos, const glm::vec2& scale, const float rotate = 0.f);
	enum class EOrientation 
	{
		LEFT,
		RIGHT
	};

	enum class EState
	{
		DOUBLE_JUMP,
		FALL,
		IDLE,
		HIT,
		JUMP,
		RUN,
		WALL_JUMP
	};

	void update(const uint64_t delta) override;

private:
	EOrientation m_orientarion = EOrientation::RIGHT;
	EState m_state = EState::IDLE;
	bool is_move = false;

	std::shared_ptr<Render::AnimatedSprite> m_sprite_run;
};