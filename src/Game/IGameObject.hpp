#pragma once
#include <glm/vec2.hpp>
#include <memory>

namespace Render
{
	class Sprite;
}


class IGameObject
{
public:
	void virtual render() const = 0;
	void virtual update(const uint64_t delta) = 0;
	glm::vec2 virtual get_pos() const;
	glm::vec2 virtual get_size() const;
	float virtual get_rotation() const;
	void virtual set_rotation(const float rotation);
	void virtual set_size(const glm::vec2& size);
	void virtual set_pos(const glm::vec2& position);

private:
	std::shared_ptr<Render::Sprite> m_sprite;
};