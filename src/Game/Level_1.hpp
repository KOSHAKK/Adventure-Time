#pragma once
#include "ILevel.hpp"
#include "NinjaFrog.hpp"
#include <memory>
#include <vector>
#include <string>
#include <array>


/*

	Q -> mycelium block 1
	W -> mycelium block 2
	E -> mycelium block 3
	Z -> mycelium dirt 1
	X -> mycelium dirt 2



	O -> EMPTY
*/






class Level_1 : public ILevel
{
public:
	Level_1(const unsigned int BLOCK_SIZE, const unsigned int width, const unsigned int height) : ILevel(BLOCK_SIZE, width, height) {	}
	void init() override;
	void render() override;
	void update(const uint64_t delta) override;

	 
private:

	std::shared_ptr<IGameObject> get_object_from_decsription(const char description, const glm::vec2& scale);



	std::shared_ptr<NinjaFrog> m_player;
	std::vector<std::string> m_map = {
		"QQQQQQQQQQQQQQQQQQ",
		"QOOOOOOOOOOOOOOOOQ",
		"QOOOOOEOOOOOOOOOOQ",
		"QOOOOOOOOOOOOOOOOQ",
		"QOOOOOOOOQQQQOOOOQ",
		"QOXOOOWOOOOOWOOOOQ",
		"QOOOOOOOOOOOQOOOOQ",
		"QOOOZOOOOQQQQOOOOQ",
		"QOOWOOOOOOOQOOOOOQ",
		"QOOWOOOOOOOQOOOOOQ",
		"QWWWWWWWWWWWWWWWWE",

	};
};