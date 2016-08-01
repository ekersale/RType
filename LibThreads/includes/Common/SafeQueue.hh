#ifndef			SAFEQUEUE_HH_
#define			SAFEQUEUE_HH_

#include		<queue>
#include                <list>
#include                <vector>
#include		"Mutex.hh"
#include		"ISafeQueue.hh"
#include		"ScopedLock.hh"
#include                "Thread.hh"

template <class T>
class			SafeQueue : public ISafeQueue<T>
{
 private:
  Mutex			*mutex;
  bool			finished;
  bool			start;
  std::vector<T>	safe_queue;

 public:
  void			push(T &);
  bool			tryPop(T * const &);
  bool			isFinished(void);
  void			setFinished(void);
  bool			pop(void);
  bool			isStart(void);
  void			setStart(void);
  int                   size(void);
  T                     at(const int);
  
  SafeQueue();
  ~SafeQueue();
};

template <class T> void push(T &);
template <class T> bool tryPop(T * const &);
template <class T> bool isFinished(void);
template <class T> void setFinished(void);
template <class T> int  pop(void);
template <class T> bool isStart(void);
template <class T> void setStart(void);
template <class T> int  size(void);
template <class T> T    at(const int);

#endif
