/*
 * Project : R-Type
 * Part : Server
 * Author : giraud_d
 */

#include        "Server.hh"

int             main(void)
{
  ThreadPool  pool;
  Server      serverPool;

  pool.scheduleThread(&serverPool, (void *)&pool);
  pool.waitThreads();
  return (0);
}
