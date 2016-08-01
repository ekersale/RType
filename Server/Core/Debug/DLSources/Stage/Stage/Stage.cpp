#include "Stage.h"
#include <iostream>
#include <time.h>

Stage::Stage()
{

}

Stage::~Stage()
{

}

t_stage*								Stage::getMob(int number, int type)
{
	t_stage *tmp = new t_stage;
	tmp->number = number;
	tmp->type = type;
	return (tmp);
}

std::vector<t_stage *>							Stage::getWaves()
{
	std::vector<t_stage *> tmp;
	int val = 0;

	for (int i = 0; i < 4; i++) // 4 ennemis par vagues
	{
		srand(time(NULL));
		val = rand() % 4 + 1 + MONSTER1;
		tmp.push_back(getMob(1, val));
	}
	return (tmp);
}

std::vector<std::vector<t_stage *> >				Stage::getStage(int level)
{
	std::vector<std::vector<t_stage *> > tmp;
	for (int i = 0; i < 6; i++) // 6 vagues
	{
		tmp.push_back(getWaves());
	}
	return (tmp);
}

std::vector<std::vector<std::vector<t_stage *> > >	Stage::getStages()
{
	std::vector<std::vector<std::vector<t_stage *> > > tmp;

	tmp.push_back(getStage(1));
	tmp.push_back(getStage(2));
	tmp.push_back(getStage(3));
	tmp.push_back(getStage(4));
	return (tmp);
}

#ifdef _WIN32
extern "C"
__declspec(dllexport) ILevels* __cdecl getPtr()
{
  ILevels *tmp = new Stage();
  
  return (tmp);
}
#else
extern "C"
{
  ILevels* getPtr() 
  {
    ILevels *tmp = new Stage();
    return (tmp);
  }
}
#endif
