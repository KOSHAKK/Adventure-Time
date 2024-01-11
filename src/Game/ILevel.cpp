#include "ILevel.hpp"
#include "../Resources/ResourceManager.hpp"
#include "MyceliumBlock.hpp"
#include <glm/vec2.hpp>

void ILevel::render()
{
	for (auto& obj : m_static_game_objects) {
		if (obj)
		{
			obj->render();
		}
	}
	for (auto& enemy : m_enemies) {
		if (enemy)
		{
			enemy->render();
		}
	}
}

void ILevel::update(const uint64_t delta)
{
	for (auto& obj : m_static_game_objects) {
		if (obj)
		{
			obj->update(delta);
		}
	}
	for (auto& enemy : m_enemies) {
		if (enemy)
		{
			enemy->update(delta);
		}
	}
}
