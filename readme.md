
# Usage

To compile, use `make`, `make all`, or `make bonus`.

## Regular pipex execution

Pipex can handle 2 or more commands. To execute:

$ ./pipex input_file command1 command2 ... commandn output_file

lua
Copy code

The output will be written to the specified output file. If the output file exists, it will be overwritten. This replicates the shell command:

$ < input_file command1 | command2 | ... | commandn > output_file

vbnet
Copy code

Each command can be given arguments and options if surrounded by quotation marks. For example:

$ ./pipex example.txt "cat" "grep x" "sed s/l/.../g" outfile.txt

csharp
Copy code

## Pipex heredoc execution

You can also run pipex with a heredoc, like this:

$ ./pipex here_doc LIMITER command1 command2 ... commandn output_file

bash
Copy code

You will then be asked to input text which will be used as input for the commands. In this case, the specified output file will not be overwritten but appended, which replicates the behavior of the shell command:

$ << LIMITER command1 | command2 | ... | commandn >> output_file

-> made 0__0