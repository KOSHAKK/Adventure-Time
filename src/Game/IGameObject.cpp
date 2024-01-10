#include "IGameObject.hpp"
#include "../Render/Sprite.hpp"

void IGameObject::render() const
{
    m_sprite->render();
}

glm::vec2 IGameObject::get_pos() const
{
    return m_sprite->get_position();
}

glm::vec2 IGameObject::get_size() const
{
    return m_sprite->get_scale();
}

float IGameObject::get_rotation() const
{
    return m_sprite->get_rotate();
}

void IGameObject::set_rotation(const float rotation)
{
    m_sprite->set_rotate(rotation);
}

void IGameObject::set_size(const glm::vec2& size)
{
    m_sprite->set_scale(size);
}

void IGameObject::set_pos(const glm::vec2& position)
{
    m_sprite->set_position(position);
}
