#include "Texture2D.hpp"
#include <iostream>

namespace Render
{
	Texture2D::Texture2D(const GLuint width,
								 const GLuint height,
								 const unsigned char* data,
								 const unsigned int channels,
								 const GLenum filter, 
								 const GLenum wrapMode)
		: m_width(width),
		  m_height(height),
		  m_mode(GL_RGBA)
	{
		switch (channels)
		{
		case 4:
			m_mode = GL_RGBA;
			break;
		case 3:
			m_mode = GL_RGB;
		}

		glGenTextures(1, &m_id);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, m_mode, m_width, m_height, 0, m_mode, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::Texture2D(Texture2D&& obj) noexcept
		: m_id(obj.m_id),
		  m_width(obj.m_width),
		  m_height(obj.m_height),
		  m_mode(GL_RGBA)
	{
		obj.m_id = 0;
	}

	Texture2D& Texture2D::operator=(Texture2D&& obj) noexcept
	{
		glDeleteTextures(1, &m_id);
		m_id = obj.m_id;
		m_width = obj.m_width;
		m_height = obj.m_height;
		m_mode = obj.m_mode;

		obj.m_id = 0;
		return *this;
	}

	void Texture2D::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture2D::add_subTexture(const std::string& name, const glm::vec2& left_bottom, const glm::vec2& right_top)
	{
		m_sub_textures.emplace(name, SubTexture2D(left_bottom, right_top));
	}

	const SubTexture2D& Texture2D::get_subTexture(const std::string& name)
	{
		auto& it = m_sub_textures.find(name);
		if (it == m_sub_textures.end())
		{
			std::cerr << "Can't find sub texture with name: " << name << std::endl;
			static const SubTexture2D ret;
			return ret;
		}
		return it->second;
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_id);
	}
}
