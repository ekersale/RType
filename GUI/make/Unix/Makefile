# To Compile GUI

NAME        =   GUI

PATH_THREAD =   ../../../LibThreads

PATH_NETWORK =  ../../../LibNetwork

PATH_GUI =   ../..

#PATH_SFML =	../../../../SFML-2.1/include
# à la sous racine du dépot, lib en dur, tmp, me contacter

SRC         =   $(PATH_THREAD)/sources/Unix/CondVar.cpp         \
                $(PATH_THREAD)/sources/Unix/Mutex.cpp           \
                $(PATH_THREAD)/sources/Unix/ScopedLock.cpp	\
                $(PATH_THREAD)/sources/Unix/Thread.cpp		\
                $(PATH_THREAD)/sources/Common/SafeQueue.cpp     \
                $(PATH_THREAD)/sources/Common/ThreadPool.cpp    \
                $(PATH_NETWORK)/sources/Unix/UClientInfo.cpp    \
                $(PATH_NETWORK)/sources/Unix/UNetwork.cpp       \
		$(PATH_GUI)/sources/DrawObject.cpp			\
		$(PATH_GUI)/sources/LoadTexture.cpp			\
		$(PATH_GUI)/sources/Mouvement.cpp				\
		$(PATH_GUI)/sources/CoreGame.cpp			\
		$(PATH_GUI)/sources/MOptions.cpp			\
		$(PATH_GUI)/sources/MGame.cpp				\
		$(PATH_GUI)/sources/MTime.cpp				\
		$(PATH_GUI)/sources/Shared.cpp				\
		$(PATH_GUI)/sources/ThreadAudio.cpp			\
		$(PATH_GUI)/sources/HandlePool.cpp			\
		$(PATH_GUI)/sources/Menu.cpp				\
		$(PATH_GUI)/sources/Sound.cpp				\
		$(PATH_GUI)/sources/Window.cpp				\
		$(PATH_GUI)/sources/CoreAction.cpp			\
		$(PATH_GUI)/sources/MControls.cpp			\
                $(PATH_GUI)/sources/main.cpp

OBJ	    =	$(SRC:.cpp=.o)

CPPFLAGS    =	-I $(PATH_THREAD)/includes/Unix                 \
                -I $(PATH_THREAD)/includes/Common               \
                -I $(PATH_NETWORK)/includes/Unix                \
                -I $(PATH_NETWORK)/includes/Common              \
                -I $(PATH_GUI)/includes
#		-I PATH_SFML					\

CXXFLAGS    =   -W -Wall -O1 -pipe -g -std=c++11

LDFLAGS		=	-lpthread -ldl -Llib/sfml/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

COMP    	=   g++

RM		    =	rm -rf

all		    :	$(NAME)
			    @echo "GUI is compiled Baby!"

$(NAME)		:	$(OBJ)
			    @$(COMP) $(INC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean		:
			    @$(RM) $(OBJ)

fclean		:	clean
			    @$(RM) $(NAME)

re		    :	fclean all

.PHONY		:   all clean fclean re
