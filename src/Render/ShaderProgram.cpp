#include "ShaderProgram.hpp"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

namespace Render
{
    ShaderProgram::ShaderProgram(const char* v_source, const char* f_source)
    {
        GLuint vs;
        if (!createShader(v_source, GL_VERTEX_SHADER, vs))
        {
            std::cerr << "VERTEX SHADER compile-time error" << std::endl;
            return;
        }

        GLuint fs;
        if (!createShader(f_source, GL_FRAGMENT_SHADER, fs))
        {
            std::cerr << "FRAGMENT SHADER compile-time error" << std::endl;
            glDeleteShader(vs);
            return;
        }


        m_id = glCreateProgram();
        glAttachShader(m_id, vs);
        glAttachShader(m_id, fs);
        glLinkProgram(m_id);

        GLint success;
        glGetProgramiv(m_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glGetShaderInfoLog(m_id, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER: Link-time error:\n" << infoLog << std::endl;
        }
        else
        {
            m_isCompiled = true;
        }

        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(m_id);
    }

    bool ShaderProgram::createShader(const char* source, const GLenum shader_type, GLuint& shaderID) const
    {
        shaderID = glCreateShader(shader_type);
        const char* code = source;
        glShaderSource(shaderID, 1, &code, nullptr);
        glCompileShader(shaderID);

        GLint success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER: Compile-time error:\n" << infoLog << std::endl;
            return false;
        }
        return true;
    }

    void ShaderProgram::use() const
    {
        glUseProgram(m_id);
    }

    ShaderProgram& Render::ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
    {
        glDeleteProgram(m_id);
        m_id = shaderProgram.m_id;
        m_isCompiled = shaderProgram.m_isCompiled;
        shaderProgram.m_id = 0;
        shaderProgram.m_isCompiled = false;
        return *this;
    }

    ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
        : m_id(shaderProgram.m_id),
          m_isCompiled(shaderProgram.m_isCompiled)
    {
        shaderProgram.m_id = 0;
        shaderProgram.m_isCompiled = false;
    }

    void ShaderProgram::set_int(const std::string& uniform_name, const int value) const
    {
        glUniform1i(glGetUniformLocation(m_id, uniform_name.c_str()), value);
    }
    void ShaderProgram::set_matrix4(const std::string& uniform_name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(m_id, uniform_name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }
}