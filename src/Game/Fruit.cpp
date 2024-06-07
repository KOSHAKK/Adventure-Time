#include "Fruit.hpp"
#include "../Resources/ResourceManager.hpp"
#include <vector>
#include <iostream>


Fruit::Fruit(const EType fruit_type, const glm::vec2& pos, const glm::vec2& scale, const float rotate)
	: m_type(fruit_type)
{
	m_object_type = IGameObject::EObjectType::FRUIT;
	static unsigned int counter = 0;
	counter++;

	constexpr uint64_t animationTime = 40;
	
	std::vector<std::pair<std::string, uint64_t>> apple_states = {
	std::make_pair("apple1", animationTime),
	std::make_pair("apple2", animationTime),
	std::make_pair("apple3", animationTime),
	std::make_pair("apple4", animationTime),
	std::make_pair("apple5", animationTime),
	std::make_pair("apple6", animationTime),
	std::make_pair("apple7", animationTime),
	std::make_pair("apple8", animationTime),
	std::make_pair("apple9", animationTime),
	std::make_pair("apple10", animationTime),
	std::make_pair("apple11", animationTime),
	std::make_pair("apple12", animationTime),
	std::make_pair("apple13", animationTime),
	std::make_pair("apple14", animationTime),
	std::make_pair("apple15", animationTime),
	std::make_pair("apple16", animationTime),
	std::make_pair("apple17", animationTime),
	};

	switch (m_type)
	{
	case Fruit::EType::Apple:
		m_sprite = ResourceManager::load_animated_sprite("fruit" + std::to_string(counter), "fruit_apple_atlas", "default_shader", static_cast<unsigned int>(scale.x), static_cast<unsigned int>(scale.y));



		m_sprite->insertState("fruit_apple_state", std::move(apple_states));
		m_sprite->setState("fruit_apple_state");
		m_sprite->set_position(pos);
		m_sprite->set_rotate(rotate);
		break;
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






	m_colliderds.emplace_back(PhysicsEngine::AABB(glm::vec2(0, 0), glm::vec2(scale.x, scale.y + 20)));
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
	//std::cout << rand() << std::endl;
	set_rotation(get_rotation() + 1);

	

	set_size(glm::vec2(static_cast<int>(get_rotation()) % 1000));
	
}
