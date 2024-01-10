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
