#include "../Resources/ResourceManager.hpp"
#include "../Render/AnimatedSprite.hpp"
#include "../Render/ShaderProgram.hpp"
#include "../Render/Texture2D.hpp"
#include "../Render/Sprite.hpp"
#include <sstream>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.hpp"


std::string ResourceManager::m_executable_path;
shaderMap ResourceManager::m_shader_programs;
textureMap ResourceManager::m_textures;
spriteMap ResourceManager::m_sprites;
animated_spriteMap ResourceManager::m_animated_sprites;


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
	auto found = m_shader_programs.find(name);

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
	auto found = m_textures.find(name);

	if (found != m_textures.end())
	{
		return found->second;
	}
	std::cerr << "Can't find texture with name: " << name << std::endl;
	return nullptr;
}

std::shared_ptr<Render::Sprite> ResourceManager::load_sprite(const std::string& name,
															 const std::string& shader_name, 
															 const std::string& texture_name, 
															 const unsigned int sprite_width,
															 const unsigned int sprite_height,
															 const std::string& sub_texture_name)
{
	auto pTexture = get_texture(texture_name);

	auto pShader = get_shader_program(shader_name);

	std::shared_ptr<Render::Sprite> newSprite = m_sprites.emplace(name, std::make_shared<Render::Sprite>(pTexture,
		pShader,
		sub_texture_name,
		glm::vec2(0.f, 0.f),
		glm::vec2(sprite_width, sprite_height))).first->second;





	return newSprite;
}

std::shared_ptr<Render::Sprite> ResourceManager::get_sprite(const std::string& name)
{
	auto found = m_sprites.find(name);

	if (found != m_sprites.end())
	{
		return found->second;
	}
	std::cerr << "Can't find sprite with name: " << name << std::endl;
	return nullptr;
}

std::shared_ptr<Render::Texture2D> ResourceManager::load_texture_atlas(const std::string& texture_name, 
																	   const std::string& path,
																	   const std::vector<std::string>& sub_textures_name,
																	   const unsigned int SubTextureWidht, 
																	   const unsigned int SubTextureHeight)
{
	auto pTexture = load_texture(std::move(texture_name), std::move(path));
	if (pTexture)
	{
		const unsigned int textureWidth = pTexture->get_width();
		const unsigned int textureHeight = pTexture->get_height();
		unsigned int currentTextureOffsetX = 0;
		unsigned int currentTextureOffsetY = textureHeight;
		for (auto& currentSubTextureName : sub_textures_name)
		{
			glm::vec2 leftBottomUV(static_cast<float>(currentTextureOffsetX) / textureWidth, static_cast<float>(currentTextureOffsetY - SubTextureHeight) / textureHeight);
			glm::vec2 rightTopUV(static_cast<float>(currentTextureOffsetX + SubTextureWidht) / textureWidth, static_cast<float>(currentTextureOffsetY) / textureHeight);
			pTexture->add_subTexture(std::move(currentSubTextureName), leftBottomUV, rightTopUV);

			currentTextureOffsetX += SubTextureWidht;
			if (currentTextureOffsetX >= textureWidth)
			{
				currentTextureOffsetX = 0;
				currentTextureOffsetY -= SubTextureHeight;
			}
		}
	}
	return pTexture;
}

std::shared_ptr<Render::AnimatedSprite> ResourceManager::load_animated_sprite(const std::string& spriteName, const std::string& textureName, const std::string& shaderName, const unsigned int spriteWidth, const unsigned int spriteHeight, const std::string& subTextureName)
{
	auto pTexture = get_texture(textureName);
	if (!pTexture)
	{
		std::cerr << "Can't find the texture: " << textureName << " for the sprite: " << spriteName << std::endl;
	}

	auto pShader = get_shader_program(shaderName);
	if (!pShader)
	{
		std::cerr << "Can't find the shader: " << shaderName << " for the sprite: " << spriteName << std::endl;
	}

	std::shared_ptr<Render::AnimatedSprite> newSprite = m_animated_sprites.emplace(textureName, std::make_shared<Render::AnimatedSprite>(pTexture,
		subTextureName,
		pShader,
		glm::vec2(0.f, 0.f),
		glm::vec2(spriteWidth, spriteHeight))).first->second;

	return newSprite;
}

std::shared_ptr<Render::AnimatedSprite> ResourceManager::get_animated_sprite(const std::string& spriteName)
{
	auto it = m_animated_sprites.find(spriteName);
	if (it != m_animated_sprites.end())
	{
		return it->second;
	}
	std::cerr << "Can't find animated sprite: " << spriteName << std::endl;
	return nullptr;
}

