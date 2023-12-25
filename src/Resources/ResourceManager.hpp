#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>

namespace Render 
{
	class ShaderProgram;
	class Texture2D;
	class Sprite;
}

typedef std::map<std::string, std::shared_ptr<Render::ShaderProgram>> shaderMap;
typedef std::map<std::string, std::shared_ptr<Render::Texture2D>> textureMap;
typedef std::map<std::string, std::shared_ptr<Render::Sprite>> spriteMap;

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


	static std::shared_ptr<Render::Texture2D> load_texture(const std::string& name, const std::string& path);
	static std::shared_ptr<Render::Texture2D> get_texture(const std::string& name);


	static std::shared_ptr<Render::Sprite> load_sprite(const std::string& name,
													   const std::string& shader_name,
													   const std::string& texture_name,
													   const unsigned int sprite_width,
													   const unsigned int sprite_height,
													   const std::string& sub_texture_name = "default");

	static std::shared_ptr<Render::Sprite> get_sprite(const std::string& name);


	static std::shared_ptr<Render::Texture2D> load_texture_atlas(const std::string& texture_name,
															     const std::string& path,
															     const std::vector<std::string>& sub_textures_name,
															     const unsigned int SubTextureWidht,
															     const unsigned int SubTextureHeight);

private:
	static std::string m_executable_path;
	static shaderMap m_shader_programs;
	static textureMap m_textures;
	static spriteMap m_sprites;
};



