#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[]) {
    // Pointer to iterate through the environment variables
    char **env_var = envp;
    char *path_value = NULL;

    // Iterate through each environment variable
    while (*env_var != NULL) {
        // Check if the current environment variable starts with "PATH="
        if (strncmp(*env_var, "PATH=", 5) == 0) {
            // Extract the value of the PATH variable (skip the first 5 characters)
            path_value = *env_var + 5;
            break;
        }
        // Move to the next environment variable
        env_var++;
    }

    // If PATH variable was found, print its value
    if (path_value != NULL) {
        printf("%s\n", path_value);
    } else {
        printf("PATH environment variable not found.\n");
    }

    return 0;
}
