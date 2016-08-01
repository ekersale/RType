#ifndef		ISAFEQUEUE_HH_
#define		ISAFEQUEUE_HH_

template <class T>
class		ISafeQueue
{
  public:
  virtual void	push(T &) = 0;
  virtual bool	tryPop(T * const &) = 0;
  virtual bool	isFinished(void) = 0;
  virtual void	setFinished(void) = 0;
  virtual bool	pop(void) = 0;
  virtual bool	isStart(void) = 0;
  virtual void	setStart(void) = 0;
  virtual int   size(void) = 0;
  virtual T     at(const int) = 0;
  
  virtual	~ISafeQueue(void){};
};

#endif
