#include "ResourceManagers.h"
#include "GameObject/Shaders.h"
#include "GameObject/Texture.h"
#include "GameObject/Models.h"
#include "GameObject/Camera.h"
#include "GameObject/Font.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/Sprite3D.h"
#include "GameObject/Text.h"


ResourceManagers::ResourceManagers()
{
	std::string dataPath = "..\\Data\\";
	m_ShaderPath = dataPath + "Shaders\\";
	m_TexturePath = dataPath + "Textures\\";
	m_ModelsPath = dataPath + "Model\\";
	m_FontPath = dataPath + "fonts\\";

	//Sound
	m_SoundsPath = dataPath + "Sound\\";
	//m_Soloud = std::make_shared<SoLoud::Soloud>();
	m_Soloud.init();
}

ResourceManagers::~ResourceManagers()
{
	m_Soloud.deinit();
}

void ResourceManagers::AddShader(const std::string& name)
{
	auto it = m_MapShader.find(name);
	if (it != m_MapShader.end())
	{
		return;
	}

	std::shared_ptr<Shaders>  shaders;
	shaders = std::make_shared<Shaders>();
	std::string vs = m_ShaderPath + name + ".vs";
	std::string fs = m_ShaderPath + name + ".fs";

	shaders->Init(vs, fs);

	m_MapShader.insert(std::pair<std::string, std::shared_ptr<Shaders>>(name, shaders));

}

void ResourceManagers::AddModel(const std::string& name)
{
	auto it = m_MapModels.find(name);
	if (it != m_MapModels.end())
	{
		return;
	}
	std::string path = m_ModelsPath + name + ".nfg";
	std::shared_ptr<Models> model = std::make_shared<Models>(path, NFG);
	m_MapModels.insert(std::pair<std::string, std::shared_ptr<Models>>(name, model));
}

void ResourceManagers::AddTexture(const std::string& name)
{
	auto it = m_MapTexture.find(name);
	if (it != m_MapTexture.end())
	{
		return;
	}
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	std::string file = m_TexturePath + name + ".tga";
	texture->Init(file.c_str(), GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR);
	m_MapTexture.insert(std::pair<std::string, std::shared_ptr<Texture>>(name, texture));
}

void ResourceManagers::AddFont(const std::string& name)
{
	auto it = m_MapFont.find(name);
	if (it != m_MapFont.end())
	{
		return;
	}
	std::string path = m_FontPath + name + ".ttf";
	std::shared_ptr<Font> font = std::make_shared<Font>(path);
	m_MapFont.insert(std::pair<std::string, std::shared_ptr<Font>>(name, font));
}

void ResourceManagers::RemoveShader(const std::string& name)
{
	m_MapShader.erase(name);
}

void ResourceManagers::RemoveModel(const std::string& name)
{
	m_MapModels.erase(name);
}

void ResourceManagers::RemoveTexture(const std::string& name)
{
	m_MapTexture.erase(name);
}

void ResourceManagers::RemoveFont(const std::string& name)
{
	m_MapFont.erase(name);
}

std::shared_ptr<Shaders> ResourceManagers::GetShader(const std::string& name)
{
	auto it = m_MapShader.find(name);
	if (it != m_MapShader.end())
	{
		return it->second;
	}

	std::shared_ptr<Shaders>  shaders;
	shaders = std::make_shared<Shaders>();
	std::string vs = m_ShaderPath + name + ".vs";
	std::string fs = m_ShaderPath + name + ".fs";

	shaders->Init(vs, fs);

	m_MapShader.insert(std::pair<std::string, std::shared_ptr<Shaders>>(name, shaders));

	return shaders;
}

std::shared_ptr<Texture> ResourceManagers::GetTexture(const std::string& name)
{
	auto it = m_MapTexture.find(name);
	if (it != m_MapTexture.end())
	{
		return it->second;
	}
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	std::string file = m_TexturePath + name + ".tga";
	texture->Init(file.c_str(), GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR);
	m_MapTexture.insert(std::pair<std::string, std::shared_ptr<Texture>>(name, texture));
	return texture;
}

std::shared_ptr<Models> ResourceManagers::GetModel(const std::string& name)
{
	auto it = m_MapModels.find(name);
	if (it != m_MapModels.end())
	{
		return it->second;
	}
	std::string path = m_ModelsPath + name + ".nfg";
	std::shared_ptr<Models> model = std::make_shared<Models>(path, NFG);
	m_MapModels.insert(std::pair<std::string, std::shared_ptr<Models>>(name, model));

	return model;
}

std::shared_ptr<Font> ResourceManagers::GetFont(const std::string& name)
{
	auto it = m_MapFont.find(name);
	if (it != m_MapFont.end())
	{
		return it->second;
	}
	std::string path = m_FontPath + name + ".ttf";
	std::shared_ptr<Font> font = std::make_shared<Font>(path);
	m_MapFont.insert(std::pair<std::string, std::shared_ptr<Font>>(name, font));
	return font;
}

void ResourceManagers::AddSound(const std::string& name)
{
	auto it = m_MapWave.find(name);
	if (it != m_MapWave.end())
	{
		return;
	}
	std::shared_ptr<SoLoud::Wav> wave;
	std::string wav = m_SoundsPath + name + ".wav";
	wave = std::make_shared<SoLoud::Wav>();
	wave->load(wav.c_str()); //load a wav file
	m_MapWave.insert(std::pair<std::string, std::shared_ptr<SoLoud::Wav>>(name, wave));
}

void ResourceManagers::PlaySound(const std::string& name, bool loop)
{
	std::shared_ptr<SoLoud::Wav> wave;
	auto it = m_MapWave.find(name);
	if (it != m_MapWave.end())
	{
		wave = it->second;
	}
	else
	{
		std::string wav = m_SoundsPath + name + ".wav";
		wave = std::make_shared<SoLoud::Wav>();
		wave->load(wav.c_str()); //load a wav file
		m_MapWave.insert(std::pair<std::string, std::shared_ptr<SoLoud::Wav>>(name, wave));
	}
	int h = m_Soloud.play(*wave);
	m_Soloud.setLooping(h, loop);
}

void ResourceManagers::PauseSound(const std::string& name)
{
	std::shared_ptr<SoLoud::Wav> wave;
	auto it = m_MapWave.find(name);
	if (it != m_MapWave.end())
	{
		wave = it->second;
	}
	m_Soloud.stopAudioSource(*wave);
}