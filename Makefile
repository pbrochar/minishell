NAME = minishell

CC = clang

SRCS_DIR = ./srcs
SRCS  = $(wildcard $(SRCS_DIR)/*.c)

INC_DIR = ./inc
OBJS = $(SRCS:.c=.o)

LIBFT = ./lib/libft.a
CFLAGS = -Wall -Wextra -Werror
INC_LIBFT = ./libft/inc

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -g -o $(NAME) $(OBJS) $(LIBFT) -ltermcap

%.o : %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(INC_LIBFT) -o $@ -c $<

clean :
	rm $(OBJS)

fclean : clean
	rm $(NAME)

re : fclean all