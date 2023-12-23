#pragma once
#include <string>
#include <map>
#include <memory>

namespace Render {
	class ShaderProgram;
}

typedef std::map<std::string, std::shared_ptr<Render::ShaderProgram>> shaderMap;

class ResourceManager
{
public:
	ResourceManager() = delete;
	static void init(const std::string& executable_path);
	static std::string get_file_text(const std::string& file_path);


	static std::shared_ptr<Render::ShaderProgram> load_shader_program(const std::string& name, 
																	  const std::string& vertex_shader_path, 
																	  const std::string& fragment_shader_path);
	static std::shared_ptr<Render::ShaderProgram> get_shader_program(const std::string& name);




private:
	static std::string m_executable_path;
	static shaderMap m_shader_programs;
};



