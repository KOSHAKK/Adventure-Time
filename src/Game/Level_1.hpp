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
	B -> left_top_border
	N -> right_top_border
	M -> right_border
	L -> left_border
	P -> top_border
	I -> right_bottom_border
	U -> left_bottom_border
	Y -> bottom_border
	T -> right_top_sub_border
	J -> left_top_sub_border

	O -> AIR
*/


namespace Render
{
	class Sprite;
}



class Level_1 : public ILevel
{
public:
	Level_1(const unsigned int BLOCK_SIZE, const unsigned int width, const unsigned int height) : ILevel(BLOCK_SIZE, width, height) {	}
	void init() override;
	void render() override;
	void update(const uint64_t delta) override;

	 
private:

	std::shared_ptr<IGameObject> get_object_from_decsription(const char description, const glm::vec2& scale);

	float m_background_pos = 0.f;

	std::shared_ptr<Render::Sprite> m_background;

	std::shared_ptr<NinjaFrog> m_player;
	std::vector<std::string> m_map = {
		"JYYYYYYYYYYYYYYYYT",
		"MOOOOOOOOOOOOOOOOL",
		"MOOOOOOOOOOOOOOOOL",
		"MOOOOOOOOOOOQOOOOL",
		"MOOOOOOOOOOQOOOOOL",
		"MOOOOOOOOOQOOOOOOL",
		"MOOOOOOOOQOOOOOOOL",
		"MOOOOOOOQOOOOOOOOL",
		"MOOOOOOOOOOOOOOOOL",
		"MOOOOOOOOOOOOOOOOL",
		"JPPPPPPPPPPPPPPPPQ",

	};
};