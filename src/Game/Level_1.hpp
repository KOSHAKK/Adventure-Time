#pragma once
#include "ILevel.hpp"
#include "NinjaFrog.hpp"
#include <memory>


class Level_1 : public ILevel
{
public:
	void init() override;

	void render() override;
	void update(const uint64_t delta) override;
	 
private:
	std::unique_ptr<NinjaFrog> m_player;
};