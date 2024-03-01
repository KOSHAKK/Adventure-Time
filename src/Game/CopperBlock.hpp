#pragma once
#include <vector>
#include <memory>

#include "IGameObject.hpp"

namespace Render
{
	class Sprite;
}

class CopperBlock : public IGameObject
{
public:
	enum class EType
	{
		COPPER_BLOCK_3x1_1,
		COPPER_BLOCK_3x1_2,
		COPPER_BLOCK_3x1_3,
		COPPER_BLOCK_1x3_1,
		COPPER_BLOCK_1x3_2,
		COPPER_BLOCK_1x3_3,
		COPPER_BLOCK_1x1_1,
		COPPER_BLOCK_2x2,
	};

	CopperBlock(const EType type, const glm::vec2& position, const glm::vec2& size = glm::vec2(64.f), const float rotate = 0.f);

	void render() const override;
	void update(const uint64_t delta) override { };
	glm::vec2 get_pos() const override;
	glm::vec2 get_size() const override;
	float get_rotation() const override;
	void set_rotation(const float rotation) override;
	void set_size(const glm::vec2& size) override;
	void set_pos(const glm::vec2& position) override;
	const float get_max_jump_power() const override { return -1.f; }

private:
	std::shared_ptr<Render::Sprite> m_sprite;
	EType m_type;
};