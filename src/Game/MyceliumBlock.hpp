#pragma once
#include "IGameObject.hpp"
#include <glm/vec2.hpp>

class MyceliumBlock : public IGameObject
{
public:
	MyceliumBlock(const glm::vec2& pos, const glm::vec2& scale, const float rotate = 0.f);
	void update(const uint64_t delta) override {	};

};