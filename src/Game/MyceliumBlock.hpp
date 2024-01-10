#pragma once
#include "IGameObject.hpp"
#include <glm/vec2.hpp>
#include <memory>

namespace Render
{
	class Sprite;
}

class MyceliumBlock : public IGameObject
{
public:
	MyceliumBlock(const glm::vec2& pos, const glm::vec2& scale, const float rotate = 0.f);
	void update(const uint64_t delta) override {	};
	void render() const override;
	glm::vec2 get_pos() const override;
	glm::vec2 get_size() const override;
	float get_rotation() const override;
	void set_rotation(const float rotation) override;
	void set_size(const glm::vec2& size) override;
	void set_pos(const glm::vec2& position) override;


private:
	std::shared_ptr<Render::Sprite> m_sprite;
};