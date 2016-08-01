#include "CoreGame.hh"
#include "MTime.hh"
#include	<string>

t_sconnect _sconnect;
int	initialiazation();

CoreGame::CoreGame()
{
	this->init();
	//this->_textureMonster1.loadFromFile(MONSTER1);
	//this->_textureAmmo1.loadFromFile("./assets/Images/AMMO1.png");
	this->_backgroundFirstPart = new sf::Sprite(this->_texture1);
	this->_backgroundSecondePart = new sf::Sprite(this->_texture2);
	
	this->_backgroundTop = new sf::Sprite(this->_textureBackgroundTop);
	this->_backgroundBottom = new sf::Sprite(this->_textureBackgroundBottom);
}

CoreGame::~CoreGame()
{
	if (this->_window != NULL)
		delete this->_window;

	if (this->_sound != NULL)
		delete this->_sound;

	if (this->_socketInGame != NULL)
		delete this->_socketInGame;

	if (this->_classShared != NULL)
		delete this->_classShared;

}

bool		CoreGame::init()
{
	if (this->loadBackgroundTexture() == false)
		return false;
	if (this->loadShipTexture() == false)
		return false;
	if (this->loadMonsterTexture() == false)
		return false;
	if (this->loadAmmoTexture() == false)
		return false;
	if (this->loadBossTexture() == false)
		return false;
	if (this->loadExplosionTexture() == false)
		return false;
	return true;
}

void		CoreGame::runCode(void *params)
{
	int		x = 0;
	double time = 0.f;
	t_movement	mouv;
	sf::Event event;
	std::string	port;

	port = this->intToString();
	this->_idSocketRoom = this->_socketInGame->connectToSocket(_sconnect.ip, port);
	this->_window->createWindow();
	this->_backgroundFirstPart->setPosition((float)x, 0.0);
	this->_backgroundSecondePart->setPosition((float(x + SIZEIMAGE)), 0);
	
#ifdef _WIN32
	FILETIME	ttmp{ 0, 0 };
	MTime		*mtime = new MTime(ttmp);
	ULARGE_INTEGER tbegin;
#else
	MTime		*mtime = new MTime;
	struct timeval start;
#endif
	while (this->_window->getWindow()->isOpen())
	{
#ifdef _WIN32
		mtime->updateClock(&tbegin);
		if ((time = mtime->getTime(tbegin)) < 0.02) {
			int res = (int)std::floor((0.02 - time) * 1000);
			Sleep(res);
		}
#else
		if ((time = mtime->getTime()) < 0.02) {
			int res = (int)std::floor((0.02 - time) * 1000);
			usleep(res);
		}
#endif
		this->_window->getWindow()->clear();

		this->_backgroundFirstPart->setPosition((float)x, 0.0);
		this->_backgroundSecondePart->setPosition((float(x + SIZEIMAGE)), 0.0);
		
		x--;
		if (x < -SIZEIMAGE)
			x = 0;

		this->_backgroundTop->setPosition(0.0, 0.0);
		this->_backgroundBottom->setPosition(0.0, 695.0);

		this->_window->getWindow()->draw(*this->_backgroundFirstPart);
		this->_window->getWindow()->draw(*this->_backgroundSecondePart);
		
		this->_window->getWindow()->draw(*this->_backgroundTop);
		this->_window->getWindow()->draw(*this->_backgroundBottom);
		if (endgame() == true)
			return ;
		updateDeath();

		drawPlayer(this->_classShared->_mapPlayer);
		drawMonster(this->_classShared->_mapMonster);
		drawAmmo(this->_classShared->_mapAmmo);
		drawBoss(this->_classShared->_mapBoss);
		drawAnExplosion();


		while (this->_window->getWindow()->pollEvent(event)){
			if (event.type == sf::Event::Closed)
				this->_window->getWindow()->close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			this->moveRight(mouv);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			this->moveLeft(mouv);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			this->moveUp(mouv);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			this->moveDown(mouv);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			this->shoot(mouv);
		this->_window->getWindow()->display();
	}
}

void		CoreGame::updateDeath()
{
	while (!this->_classShared->_idDeathObject.empty())
	{
		for (std::map<int, t_reception>::iterator it = this->_classShared->_mapMonster.begin(); it != this->_classShared->_mapMonster.end(); ++it){
			if (this->_classShared->_idDeathObject.back() == it->second.id){
				if (it != this->_classShared->_mapMonster.end()){
					this->_classShared->_mapMonster.erase(it);
					break;
				}
			}
		}
		for (std::map<int, t_reception>::iterator it = this->_classShared->_mapAmmo.begin(); it != this->_classShared->_mapAmmo.end(); ++it){
			if (this->_classShared->_idDeathObject.back() == it->second.id){
				if (it != this->_classShared->_mapAmmo.end()){
					this->_classShared->_mapAmmo.erase(it);
					break;
				}
			}
		}
		for (std::map<int, t_reception>::iterator it = this->_classShared->_mapBoss.begin(); it != this->_classShared->_mapBoss.end(); ++it){
			if (this->_classShared->_idDeathObject.back() == it->second.id){
				if (it != this->_classShared->_mapBoss.end()){
					this->_classShared->_mapBoss.erase(it);
					break;
				}
			}
		}
		//if (this->_classShared->_idDeathObject.size() > 1) //Test pour emp�cher le segfault du vector
		this->_classShared->_idDeathObject.pop_back();
	}
}

bool		CoreGame::endgame()
{
	std::string tmp;
	
	tmp = this->_classShared->_score;
	tmp += " points ";
	if (this->_classShared->_victory == true)
	{
		sf::Texture texture;
		if (!texture.loadFromFile(ENDPAGE))
			return (true);

		sf::Font font;
		font.loadFromFile("./assets/Fonts/tahomabd.ttf");

		sf::Text message(tmp, font);
		message.setPosition(sf::Vector2f(515, 305));
		message.setCharacterSize(30);
		message.setStyle(sf::Text::Bold);
		message.setColor(sf::Color::White);
		
		sf::Sprite sprite(texture);
		sprite.setPosition(0.0, 0.0);
		
		this->_window->getWindow()->draw(sprite);
		this->_window->getWindow()->draw(message);
		this->_window->getWindow()->display();
#ifdef _WIN32
		Sleep(3000);
#else
		usleep(3000 * 1000);
#endif
		initialiazation();
		return (true);
	}
	return (false);
}

int			CoreGame::getIdSocketRoom()
{
	return this->_idSocketRoom;
}

Window		*CoreGame::getWindow()
{
	return this->_window;
}

Sound	*CoreGame::getSound()
{
	return this->_sound;
}

Network	*CoreGame::getSocketInGame()
{
	return this->_socketInGame;
}

Shared	*CoreGame::getClassShared()
{
	return this->_classShared;
}

sf::Texture CoreGame::getFirstTexture()
{
	return this->_texture1;
}


sf::Texture	CoreGame::getSecondTexture()
{
	return this->_texture2;
}

sf::Sprite	*CoreGame::getFirstBackgroundSprit()
{
	return this->_backgroundFirstPart;
}

sf::Sprite	*CoreGame::getSecondBackgroundSprit()
{
	return this->_backgroundSecondePart;
}

void	CoreGame::setRoomPort(int port)
{
	this->_roomPort = port;
}

void	CoreGame::setWindow(Window *wind)
{
	this->_window = wind;
}

void	CoreGame::setSound(Sound *sound)
{
	this->_sound = sound;
}
void	CoreGame::setSocketInGame(Network *net)
{
	this->_socketInGame = net;
}

void	CoreGame::setClassShared(Shared *classShared)
{
	this->_classShared = classShared;
}

std::string	CoreGame::intToString()
{
	std::stringstream       ss;
	std::string             stringPort;

	ss << this->_roomPort;
	stringPort = ss.str();

	return stringPort;
}

sf::Texture	CoreGame::getBackgroundBottom()  const
{
	return this->_textureBackgroundBottom;
}

sf::Texture	CoreGame::getBackgroundTop() const
{
	return this->_textureBackgroundTop;
}

//Tout les GETTERS DES TEXTURES
sf::Texture	CoreGame::getTextureShip1() const
{
	return this->_textureShip1;
}

sf::Texture	CoreGame::getTextureShip2() const
{
	return this->_textureShip2;
}

sf::Texture	CoreGame::getTextureShip3() const
{
	return this->_textureShip3;
}

sf::Texture	CoreGame::getTextureShip4() const
{
	return this->_textureShip4;
}

sf::Texture	CoreGame::getTextureAmmo1() const
{
	return this->_textureAmmo1;
}

sf::Texture	CoreGame::getTextureAmmo2() const
{
	return this->_textureAmmo2;
}

sf::Texture	CoreGame::getTextureAmmo3() const
{
	return this->_textureAmmo3;
}

sf::Texture	CoreGame::getTextureMonster1() const
{
	return this->_textureMonster1;
}

sf::Texture	CoreGame::getTextureMonster2() const
{
	return this->_textureMonster2;
}

sf::Texture	CoreGame::getTextureMonster3() const
{
	return this->_textureMonster3;
}

sf::Texture	CoreGame::getTextureMonster4() const
{
	return this->_textureMonster4;
}

sf::Texture CoreGame::getTextureBoss1() const
{
	return this->_textureBoss1;
}
sf::Texture CoreGame::getTextureBoss2() const
{
	return this->_textureBoss2;
}
sf::Texture CoreGame::getTextureBoss3() const
{
	return this->_textureBoss3;
}