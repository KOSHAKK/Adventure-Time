#include "CopperBlock.hpp"
#include "../Render/Sprite.hpp"
#include "../Resources/ResourceManager.hpp"
#include <iostream>

CopperBlock::CopperBlock(const EType type, const glm::vec2& position, const glm::vec2& size, const float rotate)
	: m_type(type)
{
	m_object_type = IGameObject::EObjectType::COPPER_BLOCK;
	static int counter = 0; 
	counter++;

	switch (type)
	{
	case EType::COPPER_BLOCK_1x3_1:
		m_sprite = ResourceManager::load_sprite("coper_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(size.x), static_cast<const unsigned int>(size.y), "coper1x3_1");
		break;
	case EType::COPPER_BLOCK_1x3_2:
		m_sprite = ResourceManager::load_sprite("coper_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(size.x), static_cast<const unsigned int>(size.y), "coper1x3_2");
		break;
	case EType::COPPER_BLOCK_1x3_3:
		m_sprite = ResourceManager::load_sprite("coper_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(size.x), static_cast<const unsigned int>(size.y), "coper1x3_3");
		break;
	case EType::COPPER_BLOCK_3x1_1:
		m_sprite = ResourceManager::load_sprite("coper_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(size.x), static_cast<const unsigned int>(size.y), "coper3x1_1");
		break;
	case EType::COPPER_BLOCK_3x1_2:
		m_sprite = ResourceManager::load_sprite("coper_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(size.x), static_cast<const unsigned int>(size.y), "coper3x1_2");
		break;
	case EType::COPPER_BLOCK_3x1_3:
		m_sprite = ResourceManager::load_sprite("coper_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(size.x), static_cast<const unsigned int>(size.y), "coper3x1_3");
	case EType::COPPER_BLOCK_1x1_1:
		m_sprite = ResourceManager::load_sprite("coper_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(size.x), static_cast<const unsigned int>(size.y), "coper1x1_1");
		break;
	}
	



	m_colliderds.emplace_back(PhysicsEngine::AABB(glm::vec2(0.f), glm::vec2(size)));
	m_sprite->set_position(position);
	m_sprite->set_scale(size);
	m_sprite->set_rotate(rotate);

}

void CopperBlock::render() const
{
	m_sprite->render();
}

glm::vec2 CopperBlock::get_pos() const
{
	return m_sprite->get_position();
}

glm::vec2 CopperBlock::get_size() const
{
	return m_sprite->get_scale();
}

float CopperBlock::get_rotation() const
{
	return m_sprite->get_rotate();
}

void CopperBlock::set_rotation(const float rotation)
{
	m_sprite->set_rotate(rotation);
}

void CopperBlock::set_size(const glm::vec2& size)
{
	m_sprite->set_scale(size);
}

void CopperBlock::set_pos(const glm::vec2& position)
{
	m_sprite->set_position(position);
}
