#include		"Thread.hh"

Thread::Thread(void)
{
    status = UNLAUNCHED;
    thread = NULL;
}

Thread::~Thread(void)
{
    status = DEAD;
}

static unsigned __stdcall threadCLang(void * arguments)
{
    threadParameters    *arguments_c = reinterpret_cast<threadParameters *>(arguments);

    arguments_c->thread->runCode(arguments_c->parameters);
    delete arguments_c;
    return (0);
}

bool			Thread::waitThread(void)
{
    if (status == UNLAUNCHED)
        return (false);
    if (WaitForSingleObject(thread, INFINITE) == 0)
        return (true);
    return (false);
}

void			Thread::endThread(void)
{    
    status = DEAD;
    CloseHandle(thread);
}

bool			Thread::startThread(void * parameters)
{
    threadParameters    *tp;
    
    if (status != UNLAUNCHED)
        return (false);
    tp = new threadParameters;
    tp->parameters = parameters;
    tp->thread = this;
    if ((thread = (HANDLE)_beginthreadex(NULL, 0, threadCLang, tp, 0, &tid)) != NULL) {
        status = PENDING;
        return (true);
    }
    return (false);
}

int                     Thread::get_status(void) const {
    return (status);
}
