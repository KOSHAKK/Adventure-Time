#pragma once
#include <vector>
#include <memory>

class IGameObject;

class ILevel
{
public:
	void virtual init() = 0;
	void render();
	void update(const uint64_t delta);
	void delete_level();

protected:
	bool m_is_finish = false;

	std::vector<std::shared_ptr<IGameObject>> m_static_game_objects;
	std::vector<std::shared_ptr<IGameObject>> m_enemies;
	std::shared_ptr<IGameObject> m_player;
};