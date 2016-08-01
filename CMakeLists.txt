cmake_minimum_required(VERSION 1.0.1)
project(Server)
set(CMAKE_CXX_FLAGS "-W -Wall -O1 -pipe -g -std=c++11")
include_directories(LibThreads/includes/Unix
                    LibThreads/includes/Common
                    LibNetwork/includes/Unix
                    LibNetwork/includes/Common
                    Server/includes)
add_executable(serverCMake LibThreads/sources/Unix/CondVar.cpp
                           LibThreads/sources/Unix/Mutex.cpp
                           LibThreads/sources/Unix/ScopedLock.cpp
                           LibThreads/sources/Unix/Thread.cpp
                           LibThreads/sources/Common/SafeQueue.cpp
                           LibThreads/sources/Common/ThreadPool.cpp
                           LibNetwork/sources/Unix/UClientInfo.cpp
                           LibNetwork/sources/Unix/UNetwork.cpp
                           Server/sources/Core.cpp
                           Server/sources/MTime.cpp
                           Server/sources/Object.cpp
                           Server/sources/ObjectPull.cpp
                           Server/sources/Random.cpp
                           Server/sources/Stage.cpp
                           Server/sources/UDLLoader.cpp
                           Server/sources/WDLLoader.cpp
                           Server/sources/RcvBuff.cpp
                           Server/sources/LaunchRoom.cpp
                           Server/sources/Room.cpp
                           Server/sources/Client.cpp
                           Server/sources/Server.cpp
                           Server/sources/main.cpp)
target_link_libraries(serverCMake pthread dl)