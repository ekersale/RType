#ifndef			THREAD_HH_
#define			THREAD_HH_

#include		<pthread.h>
#include		"IThread.hh"

typedef enum		e_status
{
    UNLAUNCHED,
    PENDING,
    DEAD
}			t_status;

typedef struct          s_threadParameters
{
    void                *parameters;
    IThread             *thread;
}                       threadParameters;

class			Thread : public IThread
{
protected:
    pthread_t		thread;
    t_status		status;
public:
    bool		waitThread(void);
    void		endThread(void);
    bool		startThread(void * parameters = NULL);
    virtual void	runCode(void * parameters) = 0;
    int                 get_status(void) const;
    
    Thread(void);
    virtual ~Thread(void);
};

#endif
