#include		"SafeQueue.hh"

template <class T>
SafeQueue<T>::SafeQueue()
{
    mutex = new Mutex();
    finished = false;
    start = false;
}

template <class T>
SafeQueue<T>::~SafeQueue()
{
    delete mutex;
}

template <class T>
void			SafeQueue<T>::push(T &value)
{
    ScopedLock		lock(mutex);
    
    safe_queue.push_back(value);
}

template <class T>
bool			SafeQueue<T>::pop(void)
{
    if (isFinished() == true)
        return (false);
    return (true);
}

template <class T>
bool			SafeQueue<T>::tryPop(T * const &value)
{
    ScopedLock		lock(mutex);
    
    if (pop() == false)
        return (false);
    if (!safe_queue.empty())
    {
        *value = safe_queue.front();
        safe_queue.pop_back();
    }
    else
        return (false);
    return (true);
}

template <class T>
bool			SafeQueue<T>::isFinished(void)
{
    ScopedLock		lock(mutex);
    
    if (safe_queue.empty() == true && finished == true)
        return (true);
    return (false);
}

template <class T>
void			SafeQueue<T>::setFinished(void)
{
    ScopedLock		lock(mutex);
    
    finished = true;
}

template <class T>
void			SafeQueue<T>::setStart(void)
{
    ScopedLock		lock(mutex);
    
    start = true;
}

template <class T>
bool			SafeQueue<T>::isStart(void)
{
    ScopedLock		lock(mutex);
    
    return (start);
}

template <class T>
int			SafeQueue<T>::size(void)
{
    ScopedLock		lock(mutex);
    
    return ((int)safe_queue.size());
}

template <class T>
T			SafeQueue<T>::at(const int at)
{
    ScopedLock		lock(mutex);
    
    return (safe_queue.at(at));
}

template		SafeQueue<Thread *>::SafeQueue();
template		SafeQueue<Thread *>::~SafeQueue();

