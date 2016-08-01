#include	<iostream>
#include "Sound.hh"

Sound::Sound()
{
	_volume = 100;
}

Sound::~Sound()
{
}

bool Sound::init()
{
	sf::Music *tmp = new sf::Music;

	if (!tmp->openFromFile("./assets/Sounds/MenuIntro.wav"))
		return (false);
	_musics["menu"] = tmp;
	_musics["menu"]->setVolume((float)_volume);

	sf::SoundBuffer *soundShoot = new sf::SoundBuffer;
	if (!soundShoot->loadFromFile("./assets/Sounds/shoot.wav"))
		return (false);
	_msounds["shoot"] = soundShoot;
	sf::SoundBuffer *soundExplosion = new sf::SoundBuffer;
	if (!soundExplosion->loadFromFile("./assets/Sounds/explosion.wav"))
		return (false);
	_msounds["explosion"] = soundExplosion;

	return (true);
}

void Sound::playMusic(const std::string &piste, bool loop)
{
	if (_musics.find(piste) == _musics.end())
		return;
	_musics[piste]->setLoop(loop);
	_musics[piste]->play();
}

void Sound::stopMusic(const std::string &piste)
{
	if (_musics.find(piste) == _musics.end())
		return;
	for (int i = 100; i >= 0; i -= 2) {
		_musics[piste]->setVolume((float)i);
#ifdef _WIN32
		Sleep(10);
#else
		usleep(100); //TODO elliot
#endif
	}
	_musics[piste]->pause();
}

void Sound::soundUp(const int &rate)
{
	_volume += rate;
	if (_volume > 100)
		_volume = 100;
	for (std::map<std::string, sf::Music *>::iterator it = _musics.begin(); it != _musics.end(); ++it)
		it->second->setVolume((float)_volume);
}

void Sound::soundDown(const int &rate)
{
	_volume -= rate;
	if (_volume < 0)
		_volume = 0;
	for (std::map<std::string, sf::Music *>::iterator it = _musics.begin(); it != _musics.end(); ++it)
		it->second->setVolume((float)_volume);
}

void Sound::playSound(const std::string &name) {
	sf::Sound sound;
	sound.setBuffer(*_msounds[name]);
	sound.play();
}