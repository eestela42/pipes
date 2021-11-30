NAME = pipex
CC = gcc
INC = pipex.h
FLAGS =  -fsanitize=address

SRCS =	pipex.c		\
		utils.c		\
		libft.c		\
		ft_split.c	\
		
	
OBJS = $(SRCS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(FLAGS)

$(OBJS):	$(SRCS) $(INC)
		$(CC) $(FLAGS) -c $(SRCS)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re:		fclean all