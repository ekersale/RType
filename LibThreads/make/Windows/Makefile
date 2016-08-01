NAME		=	threads.exe

SRCS		=	../../sources/Windows/CondVar.cpp  	\
			../../sources/Windows/Mutex.cpp		\
			../../sources/Windows/ScopedLock.cpp	\
			../../sources/Windows/Thread.cpp	\
			../../sources/Common/SafeQueue.cpp	\
			../../sources/Common/ThreadPool.cpp	\
			../../sources/Common/main.cpp

OBJS		=	$(SRCS)

INC		=	-I../../includes/Common -I../../includes/Windows

LDFLAGS		=

COMP    	=       i386-mingw32-g++

RM		=	rm -rf

all		:	$(NAME)
			@echo "Thread is compiled Baby!"

$(NAME)		:	$(OBJS)
			@$(COMP) $(INC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean		:

fclean		:	clean
			@$(RM) $(NAME)

re		:	fclean all

.PHONY		:      	all clean fclean re
