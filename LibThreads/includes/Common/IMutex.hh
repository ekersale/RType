#ifndef         IMUTEX_HH_
#define         IMUTEX_HH_
#define         WAIT_TIME	1

class		IMutex
{
public:
    virtual void	lock(void) = 0;
    virtual void	unlock(void) = 0;
    virtual bool	trylock(void) = 0;
    virtual void        trylockSleep(void) = 0;
    virtual             ~IMutex(void){};
};

#endif
