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
	enum class EType
	{
		MYCELIUM_BLOCK_1,
		MYCELIUM_BLOCK_2,
		MYCELIUM_BLOCK_3,
		MYCELIUM_DIRT_1,
		MYCELIUM_DIRT_2,
	};

	MyceliumBlock(const EType block_type, const glm::vec2& pos = glm::vec2(0.f), const glm::vec2& scale = glm::vec2(0.f), const float rotate = 0.f);
	void update(const uint64_t delta) override;
	void render() const override;
	glm::vec2 get_pos() const override;
	glm::vec2 get_size() const override;
	float get_rotation() const override;
	void set_rotation(const float rotation) override;
	void set_size(const glm::vec2& size) override;
	void set_pos(const glm::vec2& position) override;


private:
	std::shared_ptr<Render::Sprite> m_sprite;
	EType m_type;
};