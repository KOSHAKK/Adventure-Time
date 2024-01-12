#include "KeyState.hpp"

std::array<bool, static_cast<size_t>(Keys::KEY_LAST)> KeyState::m_keys;

void KeyState::set_key_state(const Keys key, const bool state)
{
	m_keys[static_cast<size_t>(key)] = state;
}

bool KeyState::get_key_state(const Keys key)
{
	return m_keys[static_cast<size_t>(key)];
}
