#pragma once
#include <glm/vec2.hpp>
#include <memory>

class IGameObject
{
public:
	void virtual render() const  = 0;
	void virtual update(const uint64_t delta) = 0;
	glm::vec2 virtual get_pos() const = 0;
	glm::vec2 virtual get_size() const = 0;
	float virtual get_rotation() const = 0;
	void virtual set_rotation(const float rotation) = 0;
	void virtual set_size(const glm::vec2& size) = 0;
	void virtual set_pos(const glm::vec2& position) = 0;

};