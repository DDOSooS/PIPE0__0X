#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipex.h"

int ft_handle_proc(int fd_input, int fd_output,  char *cmd) {
    char **args;
    args = ft_pipex_parse_args(cmd);

    dup2(fd_input, STDIN_FILENO);
    dup2(fd_output, STDOUT_FILENO);

    // Example: Full path to the executable is required with execve
    char *full_path = "/bin/";  // Update this with the correct path
    char *full_cmd = ft_strjoin(full_path, args[0]);

    execve(full_cmd, args, NULL);
    perror("execve");
    exit(1);
}

void pipex(int fd_input, int fd_output, char *av[]) {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        close(fd[0]);
        ft_handle_proc(fd_input, fd[1], av[2]);
    } else {
        close(fd[1]);
        waitpid(pid, NULL, 0);
        ft_handle_proc(fd[0], fd_output, av[3]);
        fprintf(stderr, "Done for parent process\n");
    }
}

int ft_pipex_init(int ac, char *av[]) {
    int fd_input, fd_output;

    if (ac != 5) {
        ft_putstr("Usage:./pipex <input> <cmd1> <cmd2> <output>");
        return 1;
    }

    fd_input = open(av[1], O_RDONLY);
    fd_output = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if (fd_input == -1 || fd_output == -1) {
        perror("open");
        return 1;
    }

    pipex(fd_input, fd_output, av);

    close(fd_input);
    close(fd_output);
    return 0;
}

//     return ft_pipex_init(ac, av);
// }
