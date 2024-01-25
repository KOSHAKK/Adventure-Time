#include "Border.hpp"
#include "IGameObject.hpp"
#include "../Render/Sprite.hpp"
#include "../Resources/ResourceManager.hpp"


Border::Border(const EType type, const glm::vec2& position, const glm::vec2& size, const float rotate)
	: m_type(type)
{
	m_object_type = IGameObject::EObjectType::BORDER;

	static int counter = 0;
	counter++;

	switch (m_type)
	{
	case Border::EType::LEFT_TOP_BORDER:
		m_sprite = ResourceManager::load_sprite("border_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(size.x), static_cast<const unsigned int>(size.y), "left_top_border");
		break;
	case Border::EType::RIGHT_TOP_BORDER:
		m_sprite = ResourceManager::load_sprite("border_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(size.x), static_cast<const unsigned int>(size.y), "right_top_border");
		break;
	case Border::EType::LEFT_BOTTOM_BORDER:
		m_sprite = ResourceManager::load_sprite("border_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(size.x), static_cast<const unsigned int>(size.y), "left_bottom_border");
		break;
	case Border::EType::RIGHT_BOTTOM_BORDER:
		m_sprite = ResourceManager::load_sprite("border_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(size.x), static_cast<const unsigned int>(size.y), "right_bottom_border");
		break;
	case Border::EType::TOP_BORDER:
		m_sprite = ResourceManager::load_sprite("border_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(size.x), static_cast<const unsigned int>(size.y), "top_border");
		break;
	case Border::EType::LEFT_BORDER:
		m_sprite = ResourceManager::load_sprite("border_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(size.x), static_cast<const unsigned int>(size.y), "left_border");
		break;
	case Border::EType::RIGHT_BORDER:
		m_sprite = ResourceManager::load_sprite("border_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(size.x), static_cast<const unsigned int>(size.y), "right_border");
		break;
	case Border::EType::BOTTOM_BORDER:
		m_sprite = ResourceManager::load_sprite("border_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(size.x), static_cast<const unsigned int>(size.y), "bottom_border");
		break;
	case Border::EType::RIGHT_TOP_SUB_BORDER:
		m_sprite = ResourceManager::load_sprite("border_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(size.x), static_cast<const unsigned int>(size.y), "right_top_sub_border");
		break;
	case Border::EType::LEFT_TOP_SUB_BORDER:
		m_sprite = ResourceManager::load_sprite("border_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(size.x), static_cast<const unsigned int>(size.y), "left_top_sub_border");
		break;
	default:
		break;
	}



	m_sprite->set_position(position);
	m_sprite->set_scale(size);
	m_sprite->set_rotate(rotate);



	m_colliderds.emplace_back(PhysicsEngine::AABB(glm::vec2(0.f), size));
}

void Border::render() const
{
	m_sprite->render();
}

glm::vec2 Border::get_pos() const
{
	return m_sprite->get_position();
}

glm::vec2 Border::get_size() const
{
	return m_sprite->get_scale();
}

float Border::get_rotation() const
{
	return m_sprite->get_rotate();
}

void Border::set_rotation(const float rotation)
{
	m_sprite->set_rotate(rotation);
}

void Border::set_size(const glm::vec2& size)
{
	m_sprite->set_scale(size);
}

void Border::set_pos(const glm::vec2& position)
{
	m_sprite->set_position(position);
}


