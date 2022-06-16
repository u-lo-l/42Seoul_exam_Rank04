.SUFFIXES : .c .o

NAME = microshell

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

OBJS = execute.o exit.o main.o parser.o utils.o
SRCS = $(OBJS.o=.c)

all	: $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all s c clean fclean re bonus

$(NAME) : $(OBJS)
	$(CC) -o $@ $^

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@
