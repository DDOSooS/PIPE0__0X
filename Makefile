NAME = Pipe_X.a
CFLAGS = -Wall -Wextra -Werror
CC = cc
AR = ar rcs
RM = rm -rf 

SRC = pipex_utils.c pipex.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
