#ifndef			MUTEX_HH_
#define			MUTEX_HH_

#include		"IMutex.hh"
#include		<pthread.h>
#include                <unistd.h>

class			Mutex : public IMutex
{
 private:
  pthread_mutex_t	mutex;
 public:
  void			lock(void);
  void			unlock(void);
  bool			trylock(void);
  void                  trylockSleep(void);
  pthread_mutex_t* 	getMutex(void);
  
  Mutex();
  ~Mutex();
};

#endif
