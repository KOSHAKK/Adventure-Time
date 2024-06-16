#include "Fruit.hpp"
#include "../Resources/ResourceManager.hpp"
#include <vector>
#include <iostream>


Fruit::Fruit(const EType fruit_type, const glm::vec2& pos, const glm::vec2& scale, const float rotate)
	: m_type(fruit_type)
{
	m_object_type = IGameObject::EObjectType::FRUIT;
	static int counter = 0;
	counter++;

	constexpr uint64_t frame_time = 40;

	std::vector<std::pair<std::string, uint64_t>> collected_state_states = {
		std::make_pair("collected1", frame_time),
		std::make_pair("collected2", frame_time),
		std::make_pair("collected3", frame_time),
		std::make_pair("collected4", frame_time),
		std::make_pair("collected5", frame_time),
		std::make_pair("collected6", frame_time),
	};

	m_collected_sprite = ResourceManager::load_animated_sprite("fruit_collected" + std::to_string(counter), "fruit_collected_atlas", "default_shader", static_cast<unsigned int>(scale.x), static_cast<unsigned int>(scale.y), "collected1", false);
	m_collected_sprite->insertState("fruit_collected_state", std::move(collected_state_states));
	m_collected_sprite->setState("fruit_collected_state");
	m_collected_sprite->set_position(pos);
	m_collected_sprite->set_rotate(rotate);


	switch (m_type)
	{
	case Fruit::EType::Apple:
	{
		std::vector<std::pair<std::string, uint64_t>> apple_states = {
			std::make_pair("apple1", frame_time),
			std::make_pair("apple2", frame_time),
			std::make_pair("apple3", frame_time),
			std::make_pair("apple4", frame_time),
			std::make_pair("apple5", frame_time),
			std::make_pair("apple6", frame_time),
			std::make_pair("apple7", frame_time),
			std::make_pair("apple8", frame_time),
			std::make_pair("apple9", frame_time),
			std::make_pair("apple10", frame_time),
			std::make_pair("apple11", frame_time),
			std::make_pair("apple12", frame_time),
			std::make_pair("apple13", frame_time),
			std::make_pair("apple14", frame_time),
			std::make_pair("apple15", frame_time),
			std::make_pair("apple16", frame_time),
			std::make_pair("apple17", frame_time),
		};

		m_sprite = ResourceManager::load_animated_sprite("fruit" + std::to_string(counter), "fruit_apple_atlas", "default_shader", static_cast<unsigned int>(scale.x), static_cast<unsigned int>(scale.y));
		m_sprite->insertState("fruit_apple_state", std::move(apple_states));
		m_sprite->setState("fruit_apple_state");
		m_sprite->set_position(pos);
		m_sprite->set_rotate(rotate);
		break;
	}
	case Fruit::EType::Bananas:
		break;
	case Fruit::EType::Cherries:
		break;
	case Fruit::EType::Kiwi:
		break;
	case Fruit::EType::Melon:
		break;
	case Fruit::EType::Orange:
		break;
	case Fruit::EType::Pineapple:
		break;
	case Fruit::EType::Strawberry:
		break;
	default:
		break;
	}






	m_colliderds.emplace_back(PhysicsEngine::AABB(glm::vec2(0, -20), glm::vec2(scale.x, scale.y + 20)));
}

void Fruit::update(const uint64_t delta)
{
	m_sprite->update(delta);
}

void Fruit::render() const
{
	m_sprite->render();
}

glm::vec2 Fruit::get_pos() const
{
	return m_sprite->get_position();
}

glm::vec2 Fruit::get_size() const
{
	return m_sprite->get_scale();
}

float Fruit::get_rotation() const
{
	return m_sprite->get_rotate();
}

void Fruit::set_rotation(const float rotation)
{
	m_sprite->set_rotate(rotation);
}

void Fruit::set_size(const glm::vec2& size)
{
	m_sprite->set_scale(size);
}

void Fruit::set_pos(const glm::vec2& position)
{
	m_sprite->set_position(position);
}

void Fruit::on_colision()
{
	m_colliderds.clear();
	//m_sprite->destroy();
	//m_sprite->setState("fruit_apple_state");

	m_sprite = m_collected_sprite;

}
