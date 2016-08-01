#ifndef _SOUND_HH__
# define _SOUND_HH__

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <SFML/Audio.hpp>
#include <map>

class Sound
{
public:
	Sound();
	~Sound();

	bool init();
	void playMusic(const std::string &, bool);
	void stopMusic(const std::string &);
	void playSound(const std::string &);
	void soundUp(const int &);
	void soundDown(const int &);
	void soundFire();
	void soundExplosion();

private:
	std::map<std::string, sf::Music *> _musics;
	std::map<std::string, sf::SoundBuffer *> _msounds;
	int _volume;
};

#endif // !_SOUND_HH__
