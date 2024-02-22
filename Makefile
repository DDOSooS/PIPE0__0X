NAME = pipex

CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -rf 

SRC = 	src/pipe_mandatory.c src/get_path.c  \
		mini_lib/ft_strlen.c mini_lib/ft_strncmp.c mini_lib/ft_putstr.c \
		mini_lib/ft_strjoin.c mini_lib/ft_split.c mini_lib/ft_putstr_fd.c \

all: $(NAME)

bonus : $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(NAME)

fclean: clean

re: fclean all 

.PHONY: all clean fclean re bonus
