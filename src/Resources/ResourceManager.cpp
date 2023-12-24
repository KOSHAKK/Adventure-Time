#include "../Resources/ResourceManager.hpp"
#include "../Render/ShaderProgram.hpp"
#include "../Render/Texture2D.hpp"
#include <sstream>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.hpp"


std::string ResourceManager::m_executable_path;
shaderMap ResourceManager::m_shader_programs;
textureMap ResourceManager::m_textures;

void ResourceManager::init(const std::string& executable_path)
{
	size_t i = executable_path.find_last_of("/\\");
	m_executable_path = executable_path.substr(0, i);
}

std::string ResourceManager::get_file_text(const std::string& file_path)
{
	std::string path = m_executable_path + "/" + file_path;

	std::ofstream file;
	std::ifstream f;
	f.open(path);

	if (!f.is_open())
	{
		std::cerr << "Error open file " << path << std::endl;
	}

	std::stringstream ss;
	ss << f.rdbuf();
	return ss.str().c_str();
}

std::shared_ptr<Render::ShaderProgram> ResourceManager::load_shader_program(const std::string& name, 
	                                                                        const std::string& vertex_shader_path, 
	                                                                        const std::string& fragment_shader_path)
{
	std::string vs = get_file_text(vertex_shader_path);
	std::string fs = get_file_text(fragment_shader_path);


	return m_shader_programs.emplace(name, std::make_shared<Render::ShaderProgram>(vs.c_str(), fs.c_str())).first->second;
}

std::shared_ptr<Render::ShaderProgram> ResourceManager::get_shader_program(const std::string& name)
{
	auto& found = m_shader_programs.find(name);

	if (found != m_shader_programs.end())
	{
		return found->second;
	}
	std::cerr << "Can't find shader program with name: " << name << std::endl;
	return nullptr;
}

std::shared_ptr<Render::Texture2D> ResourceManager::load_texture(const std::string& name, const std::string& path)
{
	int channel{}, widht{}, height{};

	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load((m_executable_path + "/" + path).c_str(), &widht, &height, &channel, 0);

	if (!pixels)
	{
		std::cerr << "Can't load image. Path: " << path << std::endl;
		return nullptr;
	}

	std::shared_ptr<Render::Texture2D> texture = std::make_shared<Render::Texture2D>(widht, height, pixels, channel);

	stbi_image_free(pixels);
	return m_textures.emplace(name, texture).first->second;
}

std::shared_ptr<Render::Texture2D> ResourceManager::get_texture(const std::string& name)
{
	auto& found = m_textures.find(name);

	if (found != m_textures.end())
	{
		return found->second;
	}
	std::cerr << "Can't find texture with name: " << name << std::endl;
	return nullptr;
}
