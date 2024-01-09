#pragma once
#include <glad/glad.h>
#include <string>
#include <map>
#include <glm/vec2.hpp>

namespace Render
{
	struct SubTexture2D
	{
		SubTexture2D(const glm::vec2& left_bottom, const glm::vec2& right_top)
			: left_bottom(left_bottom),
			  right_top(right_top)
		{	}

		SubTexture2D()
			: left_bottom(0.f),
			right_top(1.f)
		{	}

		glm::vec2 left_bottom;
		glm::vec2 right_top;
	};


	class Texture2D
	{
	public:
		Texture2D(const GLuint width,
				  const GLuint height, 
				  const unsigned char* data, 
				  const unsigned int channels,
				  const GLenum filter =  GL_NEAREST,
				  const GLenum wrapMode = GL_CLAMP_TO_EDGE);
		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;

		Texture2D(Texture2D&& obj) noexcept;
		Texture2D& operator=(Texture2D&& obj) noexcept;

		const unsigned int get_width() const { return m_width; }
		const unsigned int get_height() const { return m_height; }

		void bind() const;

		void add_subTexture(const std::string& name, const glm::vec2& left_bottom, const glm::vec2& right_top);
		const SubTexture2D& get_subTexture(const std::string& name);

		~Texture2D();
	private:
		GLuint m_id;
		GLenum m_mode;
		GLuint m_width;
		GLuint m_height;

		std::map<std::string, SubTexture2D> m_sub_textures;
	};
}