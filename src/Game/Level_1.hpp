#pragma once
#include "ILevel.hpp"
#include "NinjaFrog.hpp"
#include <memory>
#include <vector>
#include <string>

class Level_1 : public ILevel
{
public:
	const unsigned int BLOCK_SIZE = 64;



	void init() override;

	void render() override;
	void update(const uint64_t delta) override;

	unsigned int virtual get_width() { return m_width; }
	unsigned int virtual get_height() { return m_height; }
	 
private:
	unsigned int m_width = BLOCK_SIZE * 3 * 6;
	unsigned int m_height = BLOCK_SIZE * 3 * 4;
	std::unique_ptr<NinjaFrog> m_player;
	std::vector<std::string> m_map = {
		""
	
	};
};