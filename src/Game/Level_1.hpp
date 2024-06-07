#pragma once
#include <memory>
#include <vector>
#include <string>
#include <array>

#include "ILevel.hpp"
#include "NinjaFrog.hpp"




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
	G -> left_bottom_sub_border
	F -> right_bottom_sub_border
	A -> copper_block1x3_1
	S -> copper_block1x3_2
	D -> copper_block1x3_3
	V -> copper_block3x1_1
	C -> copper_block3x1_2
	H -> copper_block3x1_3
	R -> copper_block1x1_1
	K -> apple
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

	std::shared_ptr<IGameObject> get_object_from_decsription(const char description, const glm::vec2& scale, const glm::vec2& pos);

	float m_background_pos = 0.f;

	std::shared_ptr<Render::Sprite> m_background;

	std::shared_ptr<NinjaFrog> m_player;
	std::vector<std::string> m_map = {
		"JYYYYYYYYYYYYYYYYT",
		"MOOOOOOOOOOOOOOOOL",
		"MOOOOOOOOOOOOOOOOL",
		"MOOOOOOOOOOOOOROOL",
		"MOOOOOOOOOOOOOOOOL",
		"MOOOOOOKOOOOOOOORL",
		"MQQQQQQWEQQOOOOOOL",
		"MROOOOAOAOOOQWEOOL",
		"MOOOOOSOSOOOROROOL",
		"MOOOOODODOOOROROOL",
		"GPPPPPPPPPPPPPPPPF",

	};
};