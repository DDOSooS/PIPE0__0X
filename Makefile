RED = \033[0;91m
GREEN = \033[0;92m

NAME = pipex

CFLAGS = -Wall -Wextra -Werror

CC = cc

RM = rm -rf 


FT_PRINTF_DIR = ft_printf
FT_PRINTF_LIB = $(FT_PRINTF_DIR)/libftprintf.a


SRC = 	src/pipe_mandatory.c src/get_path.c src/pipe_utils.c  \
		mini_lib/ft_strlen.c mini_lib/ft_strncmp.c mini_lib/ft_putstr.c \
		mini_lib/ft_strjoin.c mini_lib/ft_split.c mini_lib/ft_putstr_fd.c  mini_lib/ft_strdup.c \

OBJ = $(SRC:.c=.o)

SRC_BNS = src/pipe_bonus.c src/get_path.c src/pipe_utils.c  \
		mini_lib/ft_strlen.c mini_lib/ft_strncmp.c mini_lib/ft_putstr.c \
		mini_lib/ft_strjoin.c mini_lib/ft_split.c mini_lib/ft_putstr_fd.c  mini_lib/ft_strdup.c \
		gnl/get_next_line.c gnl/get_next_line_utils.c

OBJ_BNS = $(SRC_BNS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ) $(FT_PRINTF_LIB)
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
	@echo "$(GREEN) \n try to run the program like this example :\n"
	@echo "$(GREEN) ______________________________________________"
	@echo "$(RED) \n ./pipex in_file cmd1 cmd2 out_file"
	@echo "$(GREEN) ______________________________________________\n"
	@echo "$(GREEN) Where each parameter in the command line is :"
	@echo "$(RED) • in_file and out_file are files" 
	@echo "$(RED) • cmd1 - cmd2 are shell commands"

bonus : $(OBJ_BNS) $(FT_PRINTF_LIB)
	$(CC) $(CFLAGS) $^ -o $(NAME)
	@echo "$(GREEN) ________  ___  ________  _______      ___    ___  "
	@echo "$(GREEN)|\   __  \|\  \|\   __  \|\  ___ \    |\  \  /  /| "
	@echo "$(GREEN)\ \  \|\  \ \  \ \  \|\  \ \   __/|   \ \  \/  / / "
	@echo "$(GREEN) \ \   ____\ \  \ \   ____\ \  \_|/__  \ \    / /  "
	@echo "$(GREEN)  \ \  \___|\ \  \ \  \___|\ \  \_|\ \  /     \/   "
	@echo "$(GREEN)   \ \__\    \ \__\ \__\    \ \_______\/  /\   \   "
	@echo "$(GREEN)    \|__|     \|__|\|__|     \|_______/__/ /\ __\  " 
	@echo "$(GREEN)                                      |__|/ \|__|  "
	@echo "$(GREEN) \nThe Makefile has been compiled successfully!"
	@echo "$(GREEN) \n try to run the program like this example :\n"
	@echo "$(GREEN) ______________________________________________"
	@echo "$(RED) \n ./pipex in_file cmd1 cmd2 ... cmdn out_file"
	@echo "$(RED) \n ./pipex here_doc LIMITER cmd1 cmd2 out_file"
	@echo "$(GREEN) ______________________________________________\n"
	@echo "$(GREEN) Where each parameter in the command line is :"
	@echo "$(RED) • in_file and out_file are files" 
	@echo "$(RED) • cmd1 - cmdn are shell commands"



$(FT_PRINTF_LIB):
	$(MAKE) -C $(FT_PRINTF_DIR)
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJ_BNS)
	$(MAKE) -C $(FT_PRINTF_DIR) clean
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(FT_PRINTF_DIR) fclean

re: fclean all 

.PHONY: all clean fclean re bonus
