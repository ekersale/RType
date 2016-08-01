#ifndef STAGE_H_
#define STAGE_H_

#include "ILevels.h"

#ifdef _WIN32
#else
#include <stdlib.h>
#endif

class Stage : public ILevels {
public:
	Stage();
	~Stage();
	t_stage* getMob(int, int);
	std::vector<t_stage *> getWaves();
	std::vector<std::vector<t_stage *> > getStage(int);
	std::vector<std::vector<std::vector<t_stage *> > > getStages();
private:
};

#endif
