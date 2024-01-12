#pragma once
#include <array>
#include "Keys.hpp"

class KeyState
{
public:
	KeyState() = delete;

	static void set_key_state(const Keys key, const bool state);
	static bool get_key_state(const Keys key);


private:
	static std::array<bool, static_cast<size_t>(Keys::KEY_LAST)> m_keys;
};