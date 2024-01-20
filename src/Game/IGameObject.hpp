#pragma once
#include <glm/vec2.hpp>
#include <memory>
#include "../Physics/PhysicsEngine.hpp"
#include <vector>

class IGameObject
{
public:
	IGameObject();

	enum class EObjectType
	{
		MYCELIUM_BLOCK,
		PLAYER,
	};


	void virtual render() const  = 0;
	void virtual update(const uint64_t delta) = 0;
	glm::vec2 virtual get_pos() const = 0;
	glm::vec2 virtual get_size() const = 0;
	virtual bool get_direction() { return m_is_right; }
	float virtual get_rotation() const = 0;
	void virtual set_rotation(const float rotation) = 0;
	void virtual set_size(const glm::vec2& size) = 0;
	void virtual set_pos(const glm::vec2& position) = 0;
	virtual float& get_velocity() { return m_velocity; }
	EObjectType type() const { return m_object_type; }
	const std::vector<PhysicsEngine::AABB>& get_colliders() const { return m_colliderds; }
	const bool is_jump() const { return m_is_jump; }
	const bool is_fall() const { return m_is_fall; }
	void set_jump(const bool is_jump) { m_is_jump = is_jump; }
	void set_fall(const bool is_fall) { m_is_fall = is_fall; }
	const float get_jump_power() const { return m_jump_power; }
	void set_jump_power(const float power) { m_jump_power = power; }
	const float virtual get_max_jump_power() const = 0;


protected:
	float m_velocity;
	bool m_is_right = false;
	EObjectType m_object_type;
	bool m_is_jump = false;
	bool m_is_fall = false;

	float m_jump_power = 0.f;

	std::vector<PhysicsEngine::AABB> m_colliderds;


};