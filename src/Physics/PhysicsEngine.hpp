#pragma once

#include <unordered_set>
#include <memory>
#include <glm/vec2.hpp>

class ILevel;
class IGameObject;


class PhysicsEngine {
public:

    struct AABB
    {
        AABB(const glm::vec2& bottom_left, const glm::vec2& top_right)
            : bottom_left(bottom_left),
              top_right(top_right)
        {   }
        glm::vec2 bottom_left;
        glm::vec2 top_right;
    };

    ~PhysicsEngine() = delete;
    PhysicsEngine() = delete;
    PhysicsEngine(const PhysicsEngine&) = delete;
    PhysicsEngine& operator=(const PhysicsEngine&) = delete;
    PhysicsEngine& operator=(PhysicsEngine&&) = delete;
    PhysicsEngine(PhysicsEngine&&) = delete;

    static void init();
    static void terminate();

    static void update(const uint64_t delta);
    static void addDynamicGameObject(std::shared_ptr<IGameObject> p_game_object);

    static bool has_colliders_intersection(const AABB& collider1, const AABB& collider2);

    static void set_current_level(std::shared_ptr<ILevel> p_level);

private:
    static std::unordered_set<std::shared_ptr<IGameObject>> m_dynamicObjects;
    static std::shared_ptr<ILevel> m_current_level;
};