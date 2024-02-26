# Define color codes for better readability
RED = \033[0;91m
GREEN = \033[0;92m

# Target executable name
NAME = pipex

# Compiler flags
CFLAGS = -Wall -Wextra -Werror

# Compiler
CC = cc

# Command for removing files/directories
RM = rm -rf 

# Source files
SRC = 	src/pipe_mandatory.c src/get_path.c src/pipe_utils.c  \
		mini_lib/ft_strlen.c mini_lib/ft_strncmp.c mini_lib/ft_putstr.c \
		mini_lib/ft_strjoin.c mini_lib/ft_split.c mini_lib/ft_putstr_fd.c  mini_lib/ft_strdup.c \


# Object files
OBJ = $(SRC:.c=.o)

# Default target
all: $(NAME)

# Bonus target (same as default for this Makefile)
bonus: $(NAME)

# Rule to compile a .c file into a .o file
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link object files into the executable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
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

# Rule to remove compiled files
clean:
	$(RM) $(OBJ)

# Rule to remove compiled files and the executable
fclean: clean
	$(RM) $(NAME)

# Rule to remove compiled files, recompile, and recreate the executable
re: fclean all 

# Declare these targets as phony (not real files)
.PHONY: all clean fclean re bonus
