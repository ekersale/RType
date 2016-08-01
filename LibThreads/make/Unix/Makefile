NAME		=	threads

SRCS		=	../../sources/Unix/CondVar.cpp  	\
			../../sources/Unix/Mutex.cpp		\
			../../sources/Unix/ScopedLock.cpp	\
			../../sources/Unix/Thread.cpp		\
			../../sources/Common/SafeQueue.cpp	\
			../../sources/Common/ThreadPool.cpp	\
			../../sources/Common/main.cpp

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-I ../../includes/Common/ -I ../../includes/Unix/

LDFLAGS		=	-lpthread

COMP    	=       g++

RM		=	rm -rf

all		:	$(NAME)
			@echo "Thread is compiled Baby!"

$(NAME)		:	$(OBJS) 
			@$(COMP) $(INC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean		:
			@$(RM) $(OBJS)

fclean		:	clean
			@$(RM) $(NAME)

re		:	fclean all

.PHONY		:      	all clean fclean re

