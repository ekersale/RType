
# To Compile So

PATH_SO		= So

PATH_SOURCE_SO	= ../../Core/Debug/DLSources

AMMO		= AMMO

MONSTER		= Monster

STAGE		= Stage

BOSS		= Boss

COMP_GPP_SO	= g++ -shared -fPIC

# To Compile Server

NAME        =   Server

PATH_THREAD =   ../../../LibThreads

PATH_NETWORK =  ../../../LibNetwork

PATH_SERVER =   ../..

SRC         =   $(PATH_THREAD)/sources/Unix/CondVar.cpp         \
                $(PATH_THREAD)/sources/Unix/Mutex.cpp           \
                $(PATH_THREAD)/sources/Unix/ScopedLock.cpp	\
                $(PATH_THREAD)/sources/Unix/Thread.cpp		\
                $(PATH_THREAD)/sources/Common/SafeQueue.cpp     \
                $(PATH_THREAD)/sources/Common/ThreadPool.cpp    \
                $(PATH_NETWORK)/sources/Unix/UClientInfo.cpp    \
                $(PATH_NETWORK)/sources/Unix/UNetwork.cpp       \
		$(PATH_SERVER)/sources/Core.cpp			\
		$(PATH_SERVER)/sources/MTime.cpp		\
		$(PATH_SERVER)/sources/Object.cpp		\
		$(PATH_SERVER)/sources/ObjectPull.cpp		\
		$(PATH_SERVER)/sources/Random.cpp		\
		$(PATH_SERVER)/sources/Stage.cpp		\
		$(PATH_SERVER)/sources/UDLLoader.cpp		\
		$(PATH_SERVER)/sources/WDLLoader.cpp		\
                $(PATH_SERVER)/sources/RcvBuff.cpp              \
                $(PATH_SERVER)/sources/LaunchRoom.cpp           \
                $(PATH_SERVER)/sources/Room.cpp                 \
                $(PATH_SERVER)/sources/Client.cpp               \
                $(PATH_SERVER)/sources/Server.cpp               \
                $(PATH_SERVER)/sources/main.cpp

OBJ	    =	$(SRC:.cpp=.o)

CPPFLAGS    =	-I $(PATH_THREAD)/includes/Unix                 \
                -I $(PATH_THREAD)/includes/Common               \
                -I $(PATH_NETWORK)/includes/Unix                \
                -I $(PATH_NETWORK)/includes/Common              \
                -I $(PATH_SERVER)/includes

CXXFLAGS    =   -pipe -std=c++11

LDFLAGS		=	-lpthread -ldl

COMP    	=   g++

RM		    =	rm -rf

# To Compile Everythings

all		    :	$(NAME) so
			    @echo "Server is compiled Baby!"

so		:
			@$(COMP_GPP_SO) -o $(PATH_SO)/$(AMMO)-1.so  $(PATH_SOURCE_SO)/$(AMMO)/$(AMMO)-1/*.cpp
			@$(COMP_GPP_SO) -o $(PATH_SO)/$(AMMO)-2.so  $(PATH_SOURCE_SO)/$(AMMO)/$(AMMO)-2/*.cpp
			@$(COMP_GPP_SO) -o $(PATH_SO)/$(AMMO)-3.so  $(PATH_SOURCE_SO)/$(AMMO)/$(AMMO)-3/*.cpp
			@$(COMP_GPP_SO) -o $(PATH_SO)/$(AMMO)-4.so  $(PATH_SOURCE_SO)/$(AMMO)/$(AMMO)-4/*.cpp
			@$(COMP_GPP_SO) -o $(PATH_SO)/$(BOSS)-1.so  $(PATH_SOURCE_SO)/$(BOSS)/$(BOSS)-1/*.cpp
			@$(COMP_GPP_SO) -o $(PATH_SO)/$(BOSS)-2.so  $(PATH_SOURCE_SO)/$(BOSS)/$(BOSS)-2/*.cpp
			@$(COMP_GPP_SO) -o $(PATH_SO)/$(BOSS)-3.so  $(PATH_SOURCE_SO)/$(BOSS)/$(BOSS)-3/*.cpp
			@$(COMP_GPP_SO) -o $(PATH_SO)/$(MONSTER)-0.so  $(PATH_SOURCE_SO)/$(MONSTER)/$(MONSTER)-0/*.cpp
			@$(COMP_GPP_SO) -o $(PATH_SO)/$(MONSTER)-1.so  $(PATH_SOURCE_SO)/$(MONSTER)/$(MONSTER)-1/*.cpp
			@$(COMP_GPP_SO) -o $(PATH_SO)/$(MONSTER)-2.so  $(PATH_SOURCE_SO)/$(MONSTER)/$(MONSTER)-2/*.cpp
			@$(COMP_GPP_SO) -o $(PATH_SO)/$(MONSTER)-3.so  $(PATH_SOURCE_SO)/$(MONSTER)/$(MONSTER)-3/*.cpp
			@$(COMP_GPP_SO) -o $(PATH_SO)/$(STAGE).so  $(PATH_SOURCE_SO)/$(STAGE)/$(STAGE)/*.cpp

$(NAME)		:	$(OBJ)
			    @$(COMP) $(INC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean		:
			    @$(RM) $(OBJ)

fclean		:	clean
			    @$(RM) $(NAME)
				@$(RM) $(PATH_SO)/*.so

re		    :	fclean all

.PHONY		:   all clean fclean re
