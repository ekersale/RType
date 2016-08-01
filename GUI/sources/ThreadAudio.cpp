#include <iostream>
#include "ThreadAudio.hh"


ThreadAudio::ThreadAudio()
{
}


ThreadAudio::~ThreadAudio()
{
}


void	ThreadAudio::runCode(void *param)
{

	std::cout << "Params => " << param << std::endl;
	//Sleep(10);
	std::cout << "Params => " << param << std::endl;
}