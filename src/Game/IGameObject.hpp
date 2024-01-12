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


protected:
	float m_velocity;
	bool m_is_right = false;
	EObjectType m_object_type;

	std::vector<PhysicsEngine::AABB> m_colliderds;


};