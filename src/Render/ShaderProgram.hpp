#pragma once
#include <glad/glad.h>
#include <string>
#include <glm/mat4x4.hpp>

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


		void set_int(const std::string& uniform_name, const int value) const;
		void set_matrix4(const std::string& uniform_name, const glm::mat4& matrix);
	private:
		GLuint m_id = 0;
		bool m_isCompiled = false;
	};
}