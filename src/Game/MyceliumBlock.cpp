#include "MyceliumBlock.hpp"
#include "IGameObject.hpp"
#include "../Resources/ResourceManager.hpp"
#include "../Render/Sprite.hpp"
#include <string>

MyceliumBlock::MyceliumBlock(const glm::vec2& pos, const glm::vec2& scale, const float rotate)
{
	static unsigned int counter = 0;
	counter++;
	
	m_sprite = ResourceManager::load_sprite("mycelium_block" + std::to_string(counter), "default_shader", "terrain_atlas", scale.x, scale.y, "mycelium_block3x1");
	m_sprite->set_position(pos);
	m_sprite->set_rotate(rotate);
}

void MyceliumBlock::render() const
{
	m_sprite->render();
}

glm::vec2 MyceliumBlock::get_pos() const
{
	return m_sprite->get_position();
}

glm::vec2 MyceliumBlock::get_size() const
{
	return m_sprite->get_scale();
}

float MyceliumBlock::get_rotation() const
{
	return m_sprite->get_rotate();
}

void MyceliumBlock::set_rotation(const float rotation)
{
	m_sprite->set_rotate(rotation);
}

void MyceliumBlock::set_size(const glm::vec2& size)
{
	m_sprite->set_scale(size);
}

void MyceliumBlock::set_pos(const glm::vec2& position)
{
	m_sprite->set_position(position);
}
