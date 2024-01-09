#include "Texture2D.hpp"
#include "ShaderProgram.hpp"
#include "Sprite.hpp"
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>


namespace Render
{
	Render::Sprite::Sprite(std::shared_ptr<Texture2D> texture, 
		std::shared_ptr<ShaderProgram> shader, 
		const std::string& initial_subTexture,
		const glm::vec2& position, 
		const glm::vec2& size, 
		const float rotation)
		: m_pTexture(texture),
		  m_pShader(shader),
		  m_scale(size),
		  m_pos(position),
		  m_rotation(rotation)
	{
		const GLfloat vertexCoords[] = {
			// 2--3    1
			// | /   / |
			// 1    3--2

			// X  Y
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,

			1.f, 1.f,
			1.f, 0.f,
			0.f, 0.f
		};

		auto subTexture = m_pTexture->get_subTexture(initial_subTexture);

		const GLfloat textureCoords[] = {
			// U  V
			subTexture.left_bottom.x, subTexture.left_bottom.y,
			subTexture.left_bottom.x, subTexture.right_top.y,
			subTexture.right_top.x, subTexture.right_top.y,

			subTexture.right_top.x, subTexture.right_top.y,
			subTexture.right_top.x, subTexture.left_bottom.y,
			subTexture.left_bottom.x, subTexture.left_bottom.y
		};

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO_vertex_coords);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_vertex_coords);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoords), &vertexCoords, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glGenBuffers(1, &m_VBO_tex_coords);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_tex_coords);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), &textureCoords, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);


	}

	Sprite::Sprite(Sprite&& sprite) noexcept
		: m_pTexture(std::move(sprite.m_pTexture)),
		  m_pShader(std::move(sprite.m_pShader)),
		  m_scale(std::move(sprite.m_scale)),
		  m_pos(std::move(sprite.m_pos)),
		  m_rotation(sprite.m_rotation),
		  m_VAO(sprite.m_VAO),
		  m_VBO_tex_coords(sprite.m_VBO_tex_coords),
		  m_VBO_vertex_coords(sprite.m_VBO_vertex_coords)
	{
		sprite.m_VAO = 0;
		sprite.m_VBO_tex_coords = 0;
		sprite.m_VBO_vertex_coords = 0;
	}

	Sprite& Sprite::operator=(Sprite&& sprite) noexcept
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO_tex_coords);
		glDeleteBuffers(1, &m_VBO_vertex_coords);

		m_pTexture = std::move(sprite.m_pTexture);
		m_pShader = std::move(sprite.m_pShader);
		m_scale = std::move(sprite.m_scale);
		m_pos = std::move(sprite.m_pos);
		m_rotation = sprite.m_rotation;
		m_VAO = sprite.m_VAO;
		m_VBO_tex_coords = sprite.m_VBO_tex_coords;
		m_VBO_vertex_coords = sprite.m_VBO_vertex_coords;
		sprite.m_VAO = 0;
		sprite.m_VBO_tex_coords = 0;
		sprite.m_VBO_vertex_coords = 0;

		return *this;
	}
	void Sprite::render() const
	{
		m_pShader->use();


		glm::mat4 model(1.f);

		model = glm::translate(model, glm::vec3(m_pos, 0.f));
		model = glm::translate(model, glm::vec3(0.5f * m_scale.x, 0.5f * m_scale.y, 0.f));
		model = glm::rotate(model, glm::radians(m_rotation), glm::vec3(0.f, 0.f, 1.f));
		model = glm::translate(model, glm::vec3(-0.5f * m_scale.x, -0.5f * m_scale.y, 0.f));
		model = glm::scale(model, glm::vec3(m_scale, 1.f));

		glBindVertexArray(m_VAO);
		m_pShader->set_matrix4("model", model);

		glActiveTexture(GL_TEXTURE0);
		m_pTexture->bind();

		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

	void Sprite::set_position(const glm::vec2& pos)
	{
		m_pos = pos;
	}

	void Sprite::set_scale(const glm::vec2& scale)
	{
		m_scale = scale;
	}

	void Sprite::set_rotate(const float rotate)
	{
		m_rotation = rotate;
	}

	glm::vec2 Sprite::get_position() const
	{
		return m_pos;
	}

	glm::vec2 Sprite::get_scale() const
	{
		return m_scale;
	}

	float Sprite::get_rotate() const
	{
		return m_rotation;
	}

	Sprite::~Sprite()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO_tex_coords);
		glDeleteBuffers(1, &m_VBO_vertex_coords);
	}
}