#ifndef			THREADPOOL_HH_
#define			THREADPOOL_HH_

#include		"Thread.hh"
#include		"SafeQueue.hh"

class                   ThreadPool
{
private:
  SafeQueue<Thread *>   threads;
public:
  int                   scheduleThread(Thread *, void *);
  void                  waitThreads(void);
  void                  endThreads(void);
  void                  endThread(int);
  int                   size(void);
  
  ThreadPool(void);
  ~ThreadPool(void);
};

#endif
