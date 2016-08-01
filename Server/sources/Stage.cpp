#include "Stage.hh"

Stage::Stage(ILevels *lvl) : _stage(lvl->getStages()) {
	_rand = new Random();
	_rand->init();
	_lvl = 1;
	_number = _stage.size();
}

Stage::~Stage(){
}

std::vector<std::vector<t_stage *>> Stage::getStage(int stageNumber) const
{
	return (_stage[stageNumber]);
}

void Stage::setLvlStage(int level)
{
	_lvl = level - 1;
}

int Stage::getStageNumber() const
{
	return (_number);
}

std::vector<t_stage *> *Stage::getWave()
{
	std::vector<t_stage *> *tmp = new std::vector<t_stage *>;
	//static int vague = 0;

	if ((unsigned int)_lvl > _stage.size())
		return NULL;
	if (_stage[_lvl].empty())
		return NULL;
	_rand->setIntervalsX(0, _stage[_lvl].size());
	//std::cout << "Value = " << _stage[0][0][0]->type << std::endl;
	*tmp = _stage[_lvl].front();
	_stage[_lvl].erase(_stage[_lvl].begin());
	return (tmp);
}
