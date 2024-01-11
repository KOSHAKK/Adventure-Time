#pragma once
#include "IGameObject.hpp"
#include <array>

namespace Render
{
	class AnimatedSprite;
}

class NinjaFrog : public IGameObject
{
public:
	NinjaFrog(const glm::vec2& pos, const glm::vec2& scale, const float rotate = 0.f);

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

private:
	bool m_is_right = false;
	EState m_state = EState::IDLE;
	bool is_move = false;

	std::array<std::shared_ptr<Render::AnimatedSprite>, static_cast<size_t>(EState::WALL_JUMP)> m_sprites;
};