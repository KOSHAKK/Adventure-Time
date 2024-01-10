#include "ILevel.hpp"
#include "../Resources/ResourceManager.hpp"
#include "MyceliumBlock.hpp"
#include <glm/vec2.hpp>

void ILevel::render()
{
	for (auto& obj : m_static_game_objects) {
		obj->render();
	}
	for (auto& enemy : m_enemies) {
		enemy->render();
	}
	if (m_player)
	{
		m_player->render();
	}
}

void ILevel::update(const uint64_t delta)
{
	for (auto& obj : m_static_game_objects) {
		obj->update(delta);
	}
	for (auto& enemy : m_enemies) {
		enemy->update(delta);
	}
	if (m_player)
	{
		m_player->update(delta);
	}
}

void ILevel::delete_level()
{
	for (auto& obj : m_static_game_objects) {
		obj = nullptr;
	}
	for (auto& enemy : m_enemies) {
		enemy = nullptr;
	}
	m_player = nullptr;
}
