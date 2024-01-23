#pragma once
#include "IGameObject.hpp"
#include <glm/vec2.hpp>
#include <memory>

namespace Render
{
	class Sprite;
}



class Border : public IGameObject
{
public:
	enum class EType
	{
		LEFT_TOP_BORDER,
		RIGHT_TOP_BORDER,
		LEFT_BOTTOM_BORDER,
		RIGHT_BOTTOM_BORDER,
		TOP_BORDER,
		LEFT_BORDER,
		RIGHT_BORDER,
		BOTTOM_BORDER,
	};


	Border(const EType type,  const glm::vec2& position, const glm::vec2& size = glm::vec2(64.f), const float rotate = 0.f);

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