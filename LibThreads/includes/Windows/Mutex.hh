#ifndef			MUTEX_HH_
#define			MUTEX_HH_

#include		"IMutex.hh"
#include                <windows.h>
#include			<WinBase.h>
#include		<process.h>

class			Mutex : public IMutex
{
 private:
    CRITICAL_SECTION    mutex;
    bool                locked;
 public:
  void			lock(void);
  void			unlock(void);
  bool			trylock(void);
  void                  trylockSleep(void);
  CRITICAL_SECTION* 	getsMutex(void);
  
  Mutex();
  ~Mutex();
};

#endif
