#include "CoreGame.hh"
#include "MTime.hh"

#include	<string>
#include <algorithm>

void		CoreGame::drawPlayer(std::map<int, t_reception> mapMonster)
{
	while (!this->_classShared->_idDeathPlayer.empty())
	{
		for (std::map<int, t_reception>::iterator it = mapMonster.begin(); it != mapMonster.end(); ++it)
		{
			if (this->_classShared->_idDeathPlayer.back() == it->second.id)
			{
				mapMonster.erase(it);
				it = mapMonster.begin();
			}
		}
		if (this->_classShared->_idDeathPlayer.size() >= 1)
			this->_classShared->_idDeathPlayer.pop_back();
	}

	for (std::map<int, t_reception>::iterator it = mapMonster.begin(); it != mapMonster.end(); ++it){
		//1 == vivant 0  == mort
		if (it->second.alive == 1)
		{
			if (it->second.id == 0) {
				sf::Sprite sprite(_textureShip1);
				sprite.setPosition((float(it->second.pos[0])), (float(it->second.pos[1])));
				this->_window->getWindow()->draw(sprite);
			}

			if (it->second.id == 1) {
				sf::Sprite sprite(_textureShip2);
				//sprite.setPosition((float(it->second.pos[0])), (float(it->second.pos[1] + 14)));
				sprite.setPosition((float(it->second.pos[0])), (float(it->second.pos[1])));
				this->_window->getWindow()->draw(sprite);
			}

			if (it->second.id == 2) {
				sf::Sprite sprite(_textureShip3);
				sprite.setPosition((float(it->second.pos[0])), (float(it->second.pos[1] + 14)));
				this->_window->getWindow()->draw(sprite);
			}

			if (it->second.id == 3) {
				sf::Sprite sprite(_textureShip4);
				sprite.setPosition((float(it->second.pos[0])), (float(it->second.pos[1] + 14)));
				this->_window->getWindow()->draw(sprite);
			}
			/*
			if (it->second.id == 4){
			sf::Texture texture;
			if (!texture.loadFromFile(YELLOW_SHIP))
			return;

			sf::Sprite sprite(texture);
			sprite.setPosition((float(it->second.pos[0])), (float(it->second.pos[1] + 14)));
			this->_window->getWindow()->draw(sprite);
			}
			*/
		}

	}
}

void		CoreGame::drawAnExplosion() {
	for (std::vector<t_explosion *>::iterator it = _classShared->_vexplosion.begin(); it != _classShared->_vexplosion.end(); ++it) {
		_sexplosion[(*it)->i - 1].setPosition((*it)->pos[0], (*it)->pos[1]);
		if ((*it)->i - 1 >= 0)
			this->_window->getWindow()->draw(_sexplosion[(*it)->i - 1]);
		--(*it)->i;
	}
	unsigned int t = 0;
	while (t < _classShared->_vexplosion.size()) {
		if (_classShared->_vexplosion[t]->i <= 0) {
			_classShared->_vexplosion.erase(std::find(_classShared->_vexplosion.begin(),
				_classShared->_vexplosion.end(), _classShared->_vexplosion[t]));
			t = 0;
		}
		t++;
	}
}

void		CoreGame::drawMonster(std::map<int, t_reception> mapMonster)
{
	for (std::map<int, t_reception>::iterator it = mapMonster.begin(); it != mapMonster.end(); ++it){
		if (it->second.alive == 1)
		{
			/*
			sf::Texture texture;
			if (!texture.loadFromFile(MONSTER1))
			return;
			sf::Sprite sprite(texture);
			*/
			if (it->second.type == 9) {
				sf::Sprite sprite(_textureMonster1);
				sprite.setPosition((float(it->second.pos[0])), (float(it->second.pos[1])));
				this->_window->getWindow()->draw(sprite);
			}
			if (it->second.type == 10) {
				sf::Sprite sprite(_textureMonster2);
				sprite.setPosition((float(it->second.pos[0])), (float(it->second.pos[1])));
				this->_window->getWindow()->draw(sprite);
			}
			if (it->second.type == 11) {
				sf::Sprite sprite(_textureMonster3);
				sprite.setPosition((float(it->second.pos[0])), (float(it->second.pos[1])));
				this->_window->getWindow()->draw(sprite);
			}
			if (it->second.type == 12) {
				sf::Sprite sprite(_textureMonster4);
				sprite.setPosition((float(it->second.pos[0])), (float(it->second.pos[1])));
				this->_window->getWindow()->draw(sprite);
			}
		}
	}
}

void		CoreGame::drawAmmo(std::map<int, t_reception> mapMonster)
{
	for (std::map<int, t_reception>::iterator it = mapMonster.begin(); it != mapMonster.end(); ++it)
	{
		if (it->second.alive == 1)
		{
			sf::Sprite sprite(_textureAmmo1);
			sprite.setPosition((float(it->second.pos[0])), (float(it->second.pos[1] + 14)));
			this->_window->getWindow()->draw(sprite);
		}
	}
}

void		CoreGame::drawBoss(std::map<int, t_reception> mapMonster)
{
	for (std::map<int, t_reception>::iterator it = mapMonster.begin(); it != mapMonster.end(); ++it)
	{
		if (it->second.id == 0){
			sf::Sprite sprite(this->getTextureBoss1());
			sprite.setPosition((float(it->second.pos[0])), (float(it->second.pos[1])));
			this->_window->getWindow()->draw(sprite);
		}
		if (it->second.id == 1){
			sf::Sprite sprite(this->getTextureBoss2());
			sprite.setPosition(((float)it->second.pos[0]), (float(it->second.pos[1])));
			this->_window->getWindow()->draw(sprite);
		}
		if (it->second.id == 2){
			sf::Sprite sprite(this->getTextureBoss3());
			sprite.setPosition((float(it->second.pos[0])), (float(it->second.pos[1])));
			this->_window->getWindow()->draw(sprite);
		}
		if (it->second.id == 3) {
			sf::Sprite sprite(this->getTextureShip4());
			sprite.setPosition((float(it->second.pos[0])), (float(it->second.pos[1])));
			this->_window->getWindow()->draw(sprite);
		}
	}
}