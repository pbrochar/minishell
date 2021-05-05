NAME = libft.a

SRCS_DIR = ./srcs
PF_DIR = $(SRCS_DIR)/ft_printf
GNL_DIR = $(SRCS_DIR)/get_next_line

SRCS = $(wildcard $(SRCS_DIR)/*.c)
SRCS_PF = $(wildcard $(PF_DIR)/*.c)
SRCS_GNL = $(wildcard $(GNL_DIR)/*c)

OBJ = ${SRCS:.c=.o}
OBJ_PF = ${SRCS_PF:.c=.o}
OBJ_GNL = ${SRCS_GNL:.c=.o}

INC_DIR = ./inc

FLAGS = -Wall -Wextra -Werror

CC = clang

%.o : %.c
	$(CC) $(FLAGS) -c -I$(INC_DIR) $< -o ${<:.c=.o}

$(NAME) : $(OBJ) $(OBJ_PF) $(OBJ_GNL)
	ar -crs $@ $^

all : $(NAME)

clean :
	rm -f $(OBJ) 
	rm -rf $(OBJ_PF)
	rm -rf $(OBJ_GNL)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re 
