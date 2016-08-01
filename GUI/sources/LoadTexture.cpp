#include "CoreGame.hh"
#include "MTime.hh"

#include	<string>

bool	CoreGame::loadBackgroundTexture()
{
	if (!this->_texture1.loadFromFile(BACKGROUND_IMG_PATH))
		return false;
	if (!this->_texture2.loadFromFile(BACKGROUND_IMG_PATH))
		return false;
	if (!this->_textureBackgroundTop.loadFromFile(BACKGROUND_WALL_TOP))
		return false;
	if (!this->_textureBackgroundBottom.loadFromFile(BACKGROUND_WALL_BOTTOM))
		return false;
	return true;
}

bool	CoreGame::loadMonsterTexture()
{
	if (!this->_textureMonster1.loadFromFile(MONSTER1))
		return false;
	if (!this->_textureMonster2.loadFromFile(MONSTER2))
		return false;
	if (!this->_textureMonster3.loadFromFile(MONSTER3))
		return false;
	if (!this->_textureMonster4.loadFromFile(MONSTER4))
		return false;
	return true;
}


bool	CoreGame::loadAmmoTexture()
{
	if (!this->_textureAmmo1.loadFromFile(AMMO1))
		return (false);
	if (!this->_textureAmmo2.loadFromFile("./assets/Images/Ammo/ammo2.png"))
		return (false);
	if (!this->_textureAmmo3.loadFromFile("./assets/Images/Ammo/ammo3.png"))
		return (false);
	if (!this->_textureAmmo4.loadFromFile("./assets/Images/Ammo/ammo4.png"))
		return (false);
	return (true);
}

bool	CoreGame::loadShipTexture()
{
	if (!this->getTextureShip1().loadFromFile(BLUE_SHIP))
		return false;
	if (!this->_textureShip2.loadFromFile(RED_SHIP))
		return false;
	if (!this->getTextureShip3().loadFromFile(GREEN_SHIP))
		return false;
	if (!this->getTextureShip4().loadFromFile(YELLOW_SHIP))
		return false;
	return true;
}

bool	CoreGame::loadBossTexture()
{
	if (!this->getTextureBoss1().loadFromFile(BOSS1))
		return false;
	if (!this->getTextureBoss2().loadFromFile(BOSS2))
		return false;
	if (!this->getTextureBoss3().loadFromFile(BOSS3))
		return false;
	return true;
}

bool	CoreGame::loadExplosionTexture() {
	int x = 0;
	int y = 0;
	for (int i = 1; i <= 7; ++i) {
		if (_explosion[i].loadFromFile(EXPLOSION, sf::IntRect(x, y, 64, 64)) != true)
			return (false);
		_explosion[i].setSmooth(true);
		_sexplosion[i].setTexture(_explosion[i]);
		if ((i % 2) == 0) {
			y += 64;
			x = 0;
		}
		else
			x += 63;
	}
	return (true);
}