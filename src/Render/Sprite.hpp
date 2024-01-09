#pragma once
#include <glad/glad.h>
#include <memory>
#include <glm/vec2.hpp>
#include <string>

namespace Render
{
	class ShaderProgram;
	class Texture2D;

	class Sprite
	{
	public:
		Sprite(std::shared_ptr<Texture2D> texture,
			   std::shared_ptr<ShaderProgram> shader,
			   const std::string& initial_subTexture,
			   const glm::vec2& position,
			   const glm::vec2& size,
			   const float rotation = 0.f);

		Sprite(Sprite&& sprite) noexcept;
		Sprite& operator=(Sprite&& sprite) noexcept;

		virtual void render() const;

		void set_position(const glm::vec2& pos);
		void set_scale(const glm::vec2& scale);
		void set_rotate(const float rotate);


		~Sprite();

		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

	protected:
		std::shared_ptr<Texture2D> m_pTexture;
		std::shared_ptr<ShaderProgram> m_pShader;
		glm::vec2 m_pos;
		glm::vec2 m_scale;
		float m_rotation;
		GLuint m_VAO = 0;
		GLuint m_VBO_tex_coords = 0;
		GLuint m_VBO_vertex_coords = 0;
	};
}