#include "PhysicsEngine.hpp"

#include "../Game/IGameObject.hpp"
#include <iostream>
#include "../Game/ILevel.hpp"
#include "../System/Keys.hpp"
#include "../System/KeyState.hpp"

std::unordered_set<std::shared_ptr<IGameObject>> PhysicsEngine::m_dynamicObjects;
std::shared_ptr<ILevel> PhysicsEngine::m_current_level;

void PhysicsEngine::init()
{

}

void PhysicsEngine::terminate()
{
    m_dynamicObjects.clear();
    m_current_level.reset();
}

void PhysicsEngine::update(const uint64_t delta)
{
    for (auto& currentObject : m_dynamicObjects)
    {
        if (currentObject->get_velocity() > 0)
        {
            glm::vec2 new_pos;
            const auto& colliders = currentObject->get_colliders();

            if (currentObject->get_direction())
            {
                new_pos = (glm::vec2((currentObject->get_pos() + currentObject->get_velocity() * delta).x, currentObject->get_pos().y));
            }
            else
            {
                new_pos = (glm::vec2((currentObject->get_pos() - currentObject->get_velocity() * delta).x, currentObject->get_pos().y));
            }
            currentObject->set_pos(new_pos);



            const auto& objects_to_cheak = m_current_level->get_object_in_area(new_pos, new_pos + currentObject->get_size());


        }


        if (currentObject->type() == IGameObject::EObjectType::PLAYER && KeyState::get_key_state(Keys::KEY_SPACE))
        {
            currentObject->set_pos(glm::vec2(currentObject->get_pos().x, currentObject->get_pos().y + 0.2f * delta));

        }
        if (currentObject->type() == IGameObject::EObjectType::PLAYER && KeyState::get_key_state(Keys::KEY_LEFT_SHIFT))
        {
            currentObject->set_pos(glm::vec2(currentObject->get_pos().x, currentObject->get_pos().y - 0.2f * delta));
        }


       /* if (currentObject->type() == IGameObject::EObjectType::NINJA_FROG)
        {
            left_bottom = (glm::vec2(left_bottom.x, left_bottom.y - 0.02f * delta));
        }*/


    }
}

void PhysicsEngine::addDynamicGameObject(std::shared_ptr<IGameObject> pGameObject)
{
    m_dynamicObjects.insert(std::move(pGameObject));
}

bool PhysicsEngine::has_colliders_intersection(const AABB& collider1, const AABB& collider2)
{
    const glm::vec2 collider1_bottomLeft_world = collider1.bottom_left;
    const glm::vec2 collider1_topRight_world = collider1.top_right;

    const glm::vec2 collider2_bottomLeft_world = collider2.bottom_left;
    const glm::vec2 collider2_topRight_world = collider2.top_right;

    if (collider1_bottomLeft_world.x >= collider2_topRight_world.x)
    {
        return false;
    }
    if (collider1_topRight_world.x <= collider2_bottomLeft_world.x)
    {
        return false;
    }

    if (collider1_bottomLeft_world.y >= collider2_topRight_world.y)
    {
        return false;
    }
    if (collider1_topRight_world.y <= collider2_bottomLeft_world.y)
    {
        return false;
    }

    return true;
}

void PhysicsEngine::set_current_level(std::shared_ptr<ILevel> level)
{
    m_current_level.swap(level);
}

