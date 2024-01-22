NAME = Pipe_X.a

CFLAGS = -Wall -Wextra -Werror
CC = cc
AR = ar rcs
RM = rm -rf 

SRC = pipex_utils.c pipex.c strjoin.c error_handler.c ft_putstr.c
OBJ = $(SRC:.c=.o)

SRC_BNS = pipex_bonus.c 
OBJ_BNS = $(SRC_BNS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $^

bonus: $(OBJ) $(OBJ_BNS)
		$(AR) $@ $<
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJ_BNS)

fclean: clean
	$(RM) $(NAME) $(bonus)

re: fclean all 

.PHONY: all clean fclean re bonus
