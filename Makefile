NAME = pipex

CFLAGS = -Wall -Wextra -Werror
CC = cc

RM = rm -rf 
SRC = src/pipex.c src/pipex_utils.c src/strjoin.c src/ft_putstr.c src/error_handler.c

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(NAME)

fclean: clean

re: fclean all 

.PHONY: all clean fclean re bonus
