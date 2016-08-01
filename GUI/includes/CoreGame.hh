#ifndef __COREGAME_HH__
#define	__COREGAME_HH__

#include	"Windows.hh"
#include	"Network.hh"
#include	"Sound.hh"
#include	"Thread.hh"
#include	"Shared.hh"
#include	"CoreAction.hh"


#include	<sstream>

#define	SIZEIMAGE 1664
#define	SIZEWALL 25 //Taille de l'image  pour les murs

#define	BACKGROUND_IMG_PATH "./assets/Images/background.png"
#define BACKGROUND_WALL_TOP "./assets/Images/Background/backgroundTop.png"
#define BACKGROUND_WALL_BOTTOM "./assets/Images/Background/backgroundBottom.png"
#define ENDPAGE "./assets/Images/endPage.png"

#define	BLUE_SHIP "./assets/Images/Ship/spaceship_blue.png"
#define	GREEN_SHIP "./assets/Images/Ship/spaceship_green.png"
#define RED_SHIP "./assets/Images/Ship/spaceship_red.png"
#define YELLOW_SHIP "./assets/Images/Ship/spaceship_yellow.png"
#define MONSTER1 "./assets/Images/Monster/monster1.png"
#define MONSTER2 "./assets/Images/Monster/monster2.png"
#define	MONSTER3 "./assets/Images/Monster/monster3.png"
#define	MONSTER4 "./assets/Images/Monster/monster4.png"
#define BOSS1 "./assets/Images/Boss/boss.png"
#define	BOSS2 "./assets/Images/Boss/boss2.png"
#define	BOSS3 "./assets/Images/Boss/boss3.png"
#define AMMO1 "./assets/Images/Ammo/ammo1.png"
#define EXPLOSION "./assets/Images/explosion.png"


class CoreGame : public Thread
{
public:
	CoreGame();
	~CoreGame();
	bool	init();
	void	runCode(void *params);
	void	updateDeath();
	std::string	intToString();
	bool	loadBackgroundTexture();
	bool	loadAmmoTexture();
	bool	loadShipTexture();
	bool	loadMonsterTexture();
	bool	loadBossTexture();
	bool	loadExplosionTexture();
	
	//Getter
	int		getIdSocketRoom();
	Window	*getWindow();
	Sound	*getSound();
	Network	*getSocketInGame();
	Shared	*getClassShared();
	sf::Texture getFirstTexture();
	sf::Texture	getSecondTexture();
	sf::Texture	getBackgroundTop() const;
	sf::Texture	getBackgroundBottom() const;

	sf::Texture	getTextureShip1() const;
	sf::Texture	getTextureShip2() const;
	sf::Texture	getTextureShip3() const;
	sf::Texture	getTextureShip4() const;

	sf::Texture	getTextureAmmo1() const;
	sf::Texture	getTextureAmmo2() const;
	sf::Texture	getTextureAmmo3() const;
	
	sf::Texture getTextureMonster1() const;
	sf::Texture	getTextureMonster2() const;
	sf::Texture	getTextureMonster3() const;
	sf::Texture	getTextureMonster4() const;
	
	sf::Texture getTextureBoss1() const;
	sf::Texture getTextureBoss2() const;
	sf::Texture getTextureBoss3() const;

	sf::Sprite	*getFirstBackgroundSprit();
	sf::Sprite	*getSecondBackgroundSprit();

	//Setter
	void	setWindow(Window *window);
	void	setSound(Sound *sound);
	void	setSocketInGame(Network *net);
	void	setClassShared(Shared *classShared);
	void	setRoomPort(int port);

	//Envoie au serveur les mouvements
	void	moveLeft(t_movement mouv);
	void	moveRight(t_movement mouv);
	void	moveUp(t_movement mouv);
	void	moveDown(t_movement mouv);
	void	shoot(t_movement mouv);
	bool	endgame();
	

	//Afficher les object ingame
	void	drawPlayer(std::map<int, t_reception> mapMonster);
	void	drawMonster(std::map<int, t_reception> mapMonster);
	void	drawAmmo(std::map<int, t_reception> mapMonster);
	void	drawBoss(std::map<int, t_reception> mapMonster);
	void	drawAnExplosion();

	sf::Sprite	*_backgroundFirstPart;
	sf::Sprite	*_backgroundSecondePart;
	sf::Sprite	*_backgroundTop;
	sf::Sprite	*_backgroundBottom;

private:
	int		_roomPort;
	int		_idSocketRoom;
	Window	*_window;
	Sound	*_sound;
	Network	*_socketInGame;
	Shared	*_classShared;
	bool	_endPartie;
	sf::Texture	_texture1;
	sf::Texture	_texture2;
	sf::Texture	_textureBackgroundTop;
	sf::Texture	_textureBackgroundBottom;
	//Texture pour les Ship
	sf::Texture	_textureShip1;
	sf::Texture	_textureShip2;
	sf::Texture	_textureShip3;
	sf::Texture	_textureShip4;
	//Texture pour les Ammo
	sf::Texture	_textureAmmo1;
	sf::Texture	_textureAmmo2;
	sf::Texture	_textureAmmo3;
	sf::Texture _textureAmmo4;

	//Texture pour les Monstres
	sf::Texture	_textureMonster1;
	sf::Texture	_textureMonster2;
	sf::Texture	_textureMonster3;
	sf::Texture	_textureMonster4;

	//Texture pour les Boss
	sf::Texture	_textureBoss1;
	sf::Texture	_textureBoss2;
	sf::Texture	_textureBoss3;

	// Textures explosions
	sf::Texture _explosion[8];
	sf::Sprite _sexplosion[8];
};

#endif // !__COREGAME_HH__