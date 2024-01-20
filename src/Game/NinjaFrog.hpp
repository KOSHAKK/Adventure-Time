#pragma once
#include "IGameObject.hpp"
#include <array>
#include <iostream>
namespace Render
{
	class AnimatedSprite;
}

class NinjaFrog : public IGameObject
{
public:
	NinjaFrog(const glm::vec2& pos, const glm::vec2& scale, const float max_velocity = 0.2f ,const float rotate = 0.f);

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
	void render() const override;
	void set_orientation(const bool is_left);
	void set_state(const EState state);


	glm::vec2 get_pos() const override;
	glm::vec2 get_size() const override;
	float get_rotation() const override;
	void set_rotation(const float rotation) override;
	void set_size(const glm::vec2& size) override;
	void set_pos(const glm::vec2& position) override;
	float get_max_velocity() const { return m_MAX_SPEED; }
	const float get_max_jump_power() const override { return 35.f; }

private:
	EState m_state = EState::IDLE;



	float m_MAX_SPEED = 0.4f;
	std::array<std::shared_ptr<Render::AnimatedSprite>, static_cast<size_t>(EState::WALL_JUMP)> m_sprites;
};