NAME = pipex

CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -rf 

SRC = 	src/pipex.c src/get_path.c  \
		mini_lib/ft_strlen.c mini_lib/ft_strncmp.c mini_lib/ft_putstr.c \
		mini_lib/ft_strjoin.c mini_lib/ft_split.c \
		gnl/get_next_line.c gnl/get_next_line_utils.c

all: $(NAME)

bonus : $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(NAME)

fclean: clean

re: fclean all 

.PHONY: all clean fclean re bonus
