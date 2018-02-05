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

#ifndef SFGE_AUDIO_H
#define SFGE_AUDIO_H
#include <engine/engine.h>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include "utility/json_utility.h"

namespace sfge
{
class SoundBuffer;
class SoundManager;

class AudioManager : public Module
{
public:
	using Module::Module;

	void Init() override;
	void Update(sf::Time dt) override;
	void Destroy() override;

	std::shared_ptr<SoundManager> GetSoundManager();
	std::shared_ptr<SoundBuffer> GetSoundBuffer();

protected:
	std::shared_ptr<SoundManager> m_SoundManager = nullptr;
	std::shared_ptr<SoundBuffer> m_SoundBuffer = nullptr;
};

class SoundBuffer
{
public:

	unsigned int LoadSoundBuffer(std::string filename);
	std::shared_ptr<sf::SoundBuffer> GetSoundBuffer(unsigned int sound_buffer_id);

private:
	
	std::map<std::string, unsigned int> nameIdMap;
	std::map<unsigned int, std::shared_ptr<sf::SoundBuffer>> soundBufferMap;
	unsigned int increment_id = 0;
};

class Sound : public Singleton<Sound>
{
public:

	std::shared_ptr<Sound> LoadSound(json& componentJson);

	void SetSoundBuffer(std::shared_ptr<sf::SoundBuffer> newSoundBuffer);
	void Play(sf::Sound sound );

protected:
	std::string filename;
	int soundBufferId;
	sf::Sound sound;
};

class SoundManager
{
public:
	SoundManager(AudioManager& audioManager);
	void LoadSound(json& componentJson, std::shared_ptr<Sound> newSound);
protected:
	std::list<std::shared_ptr<sfge::Sound>> m_Sounds;
	AudioManager & m_AudioManager;
};

class Music : public Singleton<Music>
{

};
}
#endif // !SFGE_AUDIO
