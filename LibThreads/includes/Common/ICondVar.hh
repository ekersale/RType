#ifndef                 ICONDV_HH_
#define                 ICONDV_HH_

class                   ICondVar
{
public:
    virtual void	wait(void) = 0;
    virtual void	signal(void) = 0;
    
    virtual             ~ICondVar(void){};
};

#endif
