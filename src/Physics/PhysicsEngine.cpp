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
        if (currentObject->get_velocity() > 0 || 1) ///////////////////////////////////////// fix
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
            ///////////////
            if (currentObject->type() == IGameObject::EObjectType::PLAYER && KeyState::get_key_state(Keys::KEY_SPACE))
            {
                new_pos = glm::vec2(new_pos.x, new_pos.y + 0.2f * delta);

            }
            if (currentObject->type() == IGameObject::EObjectType::PLAYER && KeyState::get_key_state(Keys::KEY_LEFT_SHIFT))
            {
                new_pos = glm::vec2(new_pos.x, new_pos.y - 0.2f * delta);
            }
            //////////////
            const auto& objects_to_cheak = m_current_level->get_object_in_area(new_pos, new_pos + currentObject->get_size());

            bool has_collision = false;

            for (const auto& current_object_to_cheak : objects_to_cheak)
            {
                auto& colliders_to_cheak = current_object_to_cheak->get_colliders();
                if (!colliders_to_cheak.empty())
                {
                    if (has_colliders_intersection(colliders, new_pos, colliders_to_cheak, current_object_to_cheak->get_pos()))
                    {
                        has_collision = true;
                        break;
                    }
                }
            }

            if (!has_collision)
            {
                currentObject->set_pos(new_pos);
            }

        }
    }
}

void PhysicsEngine::addDynamicGameObject(std::shared_ptr<IGameObject> pGameObject)
{
    m_dynamicObjects.insert(std::move(pGameObject));
}

bool PhysicsEngine::has_colliders_intersection(const std::vector<AABB>& collider1, const glm::vec2& pos1, const std::vector<AABB>& collider2, const glm::vec2& pos2)
{
    for (const auto& currentCollider1 : collider1)
    {
        const glm::vec2 currentCollider1_bottomLeft_world = currentCollider1.bottom_left + pos1;
        const glm::vec2 currentCollider1_topRight_world = currentCollider1.top_right + pos1;
        for (const auto& currentCollider2 : collider2)
        {
            const glm::vec2 currentCollider2_bottomLeft_world = currentCollider2.bottom_left + pos2;
            const glm::vec2 currentCollider2_topRight_world = currentCollider2.top_right + pos2;

            if (currentCollider1_bottomLeft_world.x >= currentCollider2_topRight_world.x)
            {
                return false;
            }
            if (currentCollider1_topRight_world.x <= currentCollider2_bottomLeft_world.x)
            {
                return false;
            }

            if (currentCollider1_bottomLeft_world.y >= currentCollider2_topRight_world.y)
            {
                return false;
            }
            if (currentCollider1_topRight_world.y <= currentCollider2_bottomLeft_world.y)
            {
                return false;
            }
        }
    }

    return true;
}

void PhysicsEngine::set_current_level(std::shared_ptr<ILevel> level)
{
    m_current_level.swap(level);
}

