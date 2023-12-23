#pragma once
#include <glad/glad.h>
#include <string>

namespace Render
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const char* v_source, const char* f_source);
		~ShaderProgram();
		bool createShader(const char* source, const GLenum shader_type, GLuint& shaderID) const;
		void use() const;

		bool isCompiled() const { return m_isCompiled; }

		ShaderProgram() = delete;
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
	private:
		GLuint m_id = 0;
		bool m_isCompiled = false;
	};
}