#pragma once
#include "IGameObject.hpp"
#include <memory>
#include "../Render/AnimatedSprite.hpp"

class Fruit : public IGameObject
{
public:

	enum class EState
	{
		ACTIVE,
		COLLECTED
	};

	enum class EType
	{
		Apple,
		Bananas,
		Cherries,
		Kiwi,
		Melon,
		Orange,
		Pineapple,
		Strawberry,
	};
	Fruit(const EType fruit_type, const glm::vec2& pos, const glm::vec2& scale, const float rotate = 0.f);
	~Fruit() {	}

	void update(const uint64_t delta) override;
	void render() const override;
	glm::vec2 get_pos() const override;
	glm::vec2 get_size() const override;
	float get_rotation() const override;
	void set_rotation(const float rotation) override;
	void set_size(const glm::vec2& size) override;
	void set_pos(const glm::vec2& position) override;
	void on_colision() override;



private:
	EType m_type;
	std::shared_ptr<Render::AnimatedSprite> m_sprite;
};
