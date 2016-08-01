#ifndef _STAGE_HH__
# define _STAGE_HH__

#include "ILevels.hh"
#ifdef _WIN32
#include "WDLLoader.hh"
#else
#include "UDLLoader.hh"
#endif
#include "IStage.hh"

class Stage : public IStage
{
public:
	Stage(ILevels *);
	~Stage();

	std::vector<std::vector<t_stage *>> getStage(int) const;
	std::vector<t_stage *> *getWave();
	void setLvlStage(int);
	int getStageNumber() const;

private:
	std::vector<std::vector<std::vector<t_stage *>>> _stage;
	Random *_rand;
#ifdef _WIN32
	WDLLoader *dll;
#else
	UDLLoader *dll;
#endif
	int _lvl;
	int _number;
};

#endif // !_STAGE_HH__
