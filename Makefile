RED = \033[0;91m
GREEN = \033[0;92m
NAME = pipex

CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -rf 

SRC = 	src/pipe_mandatory.c src/get_path.c  \
		mini_lib/ft_strlen.c mini_lib/ft_strncmp.c mini_lib/ft_putstr.c \
		mini_lib/ft_strjoin.c mini_lib/ft_split.c mini_lib/ft_putstr_fd.c \
		gnl/get_next_line.c gnl/get_next_line_utils.c

all: $(NAME)

bonus : $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@
	@echo "$(GREEN) ________  ___  ________  _______      ___    ___  "
	@echo "$(GREEN)|\   __  \|\  \|\   __  \|\  ___ \    |\  \  /  /| "
	@echo "$(GREEN)\ \  \|\  \ \  \ \  \|\  \ \   __/|   \ \  \/  / / "
	@echo "$(GREEN) \ \   ____\ \  \ \   ____\ \  \_|/__  \ \    / /  "
	@echo "$(GREEN)  \ \  \___|\ \  \ \  \___|\ \  \_|\ \  /     \/   "
	@echo "$(GREEN)   \ \__\    \ \__\ \__\    \ \_______\/  /\   \   "
	@echo "$(GREEN)    \|__|     \|__|\|__|     \|_______/__/ /\ __\  " 
	@echo "$(GREEN)                                      |__|/ \|__|  "
	@echo "$(GREEN) \nThe Makefile has been compiled succesfuly!"
	@echo "$(GREEN) \n try to run the program like this exemple :\n"
	@echo "$(GREEN) ______________________________________________"
	@echo "$(RED) \n ./pipex in_file cmd1 cmd2 out_file"
	@echo "$(GREEN) ______________________________________________\n"
	@echo "$(GREEN) Where each parameter in the command line is :"
	@echo "$(RED) • in_file and out_file are files" 
	@echo "$(RED) • cmd1 - cmd2 are shell commands"
clean:
	$(RM) $(NAME)

fclean: clean

re: fclean all 

.PHONY: all clean fclean re bonus
