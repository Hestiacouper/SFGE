/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <graphics/graphics.h>

#include <engine/log.h>
#include <engine/config.h>

//Dependencies includes
#include <SFML/Graphics/RenderWindow.hpp>
#include "imgui-SFML.h"
#include "imgui.h"

#include <sstream>

namespace sfge
{
GraphicsManager::GraphicsManager(Engine& engine) :
		Module(engine), m_SpriteManager(engine, *this), 
		m_ShapeManager(engine), m_TextureManager(engine)
{
}
void GraphicsManager::Init()
{
	if (const auto configPtr = m_Engine.GetConfig().lock())
	{

		if (!m_Windowless)
		{
			m_Window = std::make_shared<sf::RenderWindow>(
				sf::VideoMode(configPtr->screenResolution.x, configPtr->screenResolution.y),
				"SFGE 0.1");
			if (configPtr->maxFramerate)
			{
				m_Window->setFramerateLimit(configPtr->maxFramerate);
				CheckVersion();
			}
		}
	}
	else
	{
		Log::GetInstance()->Error("[Error] Config is null from Graphics Manager");
		
	}
	m_TextureManager.Init();

}

void GraphicsManager::Update(sf::Time dt)
{
	if (!m_Windowless)
	{
		m_Window->clear();

		m_SpriteManager.Update(dt);
		m_ShapeManager.Update(dt);
		m_SpriteManager.Draw(*m_Window);

		m_ShapeManager.Draw(*m_Window);
	}
}

void GraphicsManager::Display()
{
	if (!m_Windowless)
	{
		m_Window->display();
	}
}

void GraphicsManager::DrawLine(sf::Vector2f from, sf::Vector2f to, sf::Color color)
{
	sf::Vertex vertices[2] =
	{
	    sf::Vertex(from, color),
	    sf::Vertex(to, color)
	};

	m_Window->draw(vertices, 2, sf::Lines);
}

std::shared_ptr<sf::RenderWindow> GraphicsManager::GetWindow()
{
	return m_Window;
}

SpriteManager& GraphicsManager::GetSpriteManager()
{
	return m_SpriteManager;
}

TextureManager& GraphicsManager::GetTextureManager()
{
	return m_TextureManager;
}

ShapeManager& GraphicsManager::GetShapeManager()
{
	return m_ShapeManager;
}

void GraphicsManager::CheckVersion() const
{
	sf::ContextSettings settings = m_Window->getSettings();
	std::stringstream log_message;
	log_message << "OpenGL version: " << settings.majorVersion << "." << settings.minorVersion << std::endl;

	Log::GetInstance()->Msg(log_message.str());
}

void checkVersion()
{

}


void GraphicsManager::Destroy()
{
	Clear();
	Collect();

	m_Window = nullptr;
	ImGui::SFML::Shutdown();
}

void GraphicsManager::Clear()
{
	m_TextureManager.Clear();
	m_SpriteManager.Reset();
}

void GraphicsManager::Collect()
{

	m_TextureManager.Collect();
	m_SpriteManager.Collect();
}

}
