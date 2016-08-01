#ifndef _ISTAGE_HH__
# define _ISTAGE_HH__

#include <vector>
#include "Elems.hh"
#include "Random.hh"

class IStage
{
public:
	virtual std::vector<std::vector<t_stage *>> getStage(int) const = 0;
	virtual std::vector<t_stage *> *getWave() = 0;
	virtual void setLvlStage(int) = 0;
	virtual int getStageNumber() const = 0;
};

#endif // !_ISTAGE_HH__
