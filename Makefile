RED = \033[0;91m
GREEN = \033[0;92m

NAME = pipex

NAME_BONUS = pipex_bonus

CFLAGS = -Wall -Wextra -Werror

CC = cc

RM = rm -rf 

SRC = 	src/pipe_mandatory.c src/get_path.c src/pipe_utils.c  \
		mini_lib/ft_strlen.c mini_lib/ft_strncmp.c mini_lib/ft_putstr.c \
		mini_lib/ft_strjoin.c mini_lib/ft_split.c mini_lib/ft_putstr_fd.c  mini_lib/ft_strdup.c \

OBJ = $(SRC:.c=.o)

SRC_BNS = src/pipe_bonus.c src/get_path.c src/pipe_utils.c src/pipe_utils_bonus.c  \
		mini_lib/ft_strlen.c mini_lib/ft_strncmp.c mini_lib/ft_putstr.c \
		mini_lib/ft_strjoin.c mini_lib/ft_split.c mini_lib/ft_putstr_fd.c  mini_lib/ft_strdup.c \
		gnl/get_next_line.c gnl/get_next_line_utils.c

OBJ_BNS = $(SRC_BNS:.c=.o)

all: $(NAME)

bonus : $(NAME_BONUS)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $^  -o $@
	@echo "$(GREEN) ________  ___  ________  _______      ___    ___  "
	@echo "$(GREEN)|\   __  \|\  \|\   __  \|\  ___ \    |\  \  /  /| "
	@echo "$(GREEN)\ \  \|\  \ \  \ \  \|\  \ \   __/|   \ \  \/  / / "
	@echo "$(GREEN) \ \   ____\ \  \ \   ____\ \  \_|/__  \ \    / /  "
	@echo "$(GREEN)  \ \  \___|\ \  \ \  \___|\ \  \_|\ \  /     \/   "
	@echo "$(GREEN)   \ \__\    \ \__\ \__\    \ \_______\/  /\   \   "
	@echo "$(GREEN)    \|__|     \|__|\|__|     \|_______/__/ /\ __\  " 
	@echo "$(GREEN)                                      |__|/ \|__|  "
	@echo "$(GREEN) \nThe Makefile has been compiled successfully!"
	@echo "$(GREEN) \n try to run the program like this example :"
	@echo "$(GREEN) ______________________________________________"
	@echo "$(RED) \n ./pipex in_file cmd1 cmd2 out_file"
	@echo "$(GREEN) ______________________________________________\n"
	@echo "$(GREEN) Where each parameter in the command line is :"
	@echo "$(RED) • in_file and out_file are files" 
	@echo "$(RED) • cmd1 - cmd2 are shell commands"

$(NAME_BONUS) : $(OBJ_BNS)
	$(CC) $(CFLAGS) $^ -o $@
	@echo "$(GREEN) ________  ___  ________  _______      ___    ___      __     "
	@echo "$(GREEN)|\   __  \|\  \|\   __  \|\  ___ \    |\  \  /  /|    |  |    "
	@echo "$(GREEN)\ \  \|\  \ \  \ \  \|\  \ \   __/|   \ \  \/  / / ___|  |___ "
	@echo "$(GREEN) \ \   ____\ \  \ \   ____\ \  \_|/__  \ \    / / |___    ___|"
	@echo "$(GREEN)  \ \  \___|\ \  \ \  \___|\ \  \_|\ \  /     \/     _|  |    "
	@echo "$(GREEN)   \ \__\    \ \__\ \__\    \ \_______\/  /\   \     \|__|    "
	@echo "$(GREEN)    \|__|     \|__|\|__|     \|_______/__/ /\ __\             " 
	@echo "$(GREEN)                                      |__|/ \|__|             "
	@echo "$(GREEN) \nThe Makefile has been compiled successfully!"
	@echo "$(GREEN) \n try to run the program like this example :"
	@echo "$(GREEN) ______________________________________________"
	@echo "$(RED) \n ./pipex in_file cmd1 cmd2 ... cmdn out_file"
	@echo "$(RED) \n ./pipex here_doc LIMITER cmd1 cmd2 out_file"
	@echo "$(GREEN) ______________________________________________\n"
	@echo "$(GREEN) Where each parameter in the command line is :"
	@echo "$(RED) • in_file and out_file are files" 
	@echo "$(RED) • cmd1 - cmdn are shell commands"

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJ_BNS)

fclean: 
	$(RM) $(NAME) $(OBJ) $(OBJ_BNS) $(NAME_BONUS)

re: fclean all 

.PHONY: all clean fclean re bonus
