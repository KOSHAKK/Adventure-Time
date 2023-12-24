#pragma once
#include <glad/glad.h>
#include <string>

namespace Render
{
	class Texture2D
	{
	public:
		Texture2D(const GLuint width,
				  const GLuint height, 
				  const unsigned char* data, 
				  const unsigned int channels,
				  const GLenum filter = GL_NEAREST, 
				  const GLenum wrapMode = GL_CLAMP_TO_EDGE);
		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;

		Texture2D(Texture2D&& obj) noexcept;
		Texture2D& operator=(Texture2D&& obj) noexcept;

		void bind() const;

		~Texture2D();
	private:
		GLuint m_id;
		GLenum m_mode;
		GLuint m_width;
		GLuint m_height;
	};
}