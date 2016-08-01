#ifndef                         ITHREAD_HH_
#define                         ITHREAD_HH_

class                           IThread
{
public:
    virtual bool		waitThread(void) = 0;
    virtual void		endThread(void) = 0;
    virtual bool		startThread(void * parameters) = 0;
    virtual void                runCode(void * parameters) = 0;
    virtual int                 get_status(void) const = 0;
    
    virtual                     ~IThread(void){};
};

#endif
