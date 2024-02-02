#include <stdio.h>
#include <unistd.h>
#include <errno.h> // for errno

int main() {
    // Define arguments for the execve command
    char *args[] = {"env", NULL};

    // Define environment variables
    char *envp[] = {NULL};  // For simplicity, environment variables are left empty

    // Use execve to execute the env command
    if (execve("/usr/bin/env", args, envp) == -1) {
        perror("execve");
        return 1;  // Indicate failure
    }

    // execve will only return if an error occurs
    return 0; // Unreachable, unless execve fails
}
