# PIPEX
42 School project aimed at replicating Unix pipe behavior. It executes a set of commands chained by pipes by handling file descriptors and child processes.

Following the [42 norm](https://github.com/42school/norminette)

## Skills developed
- Handle input/output redirection
- Manage child processes
- Understand how Unix pipelines work
- Work with environment paths and access permissions

## How to run
```make```
OR to handle multiple pipes and a heredoc
```make bonus```

### Example usage
```
make
./pipex infile command1 command2 outfile

make bonus
./pipex_bonus infile command1 command2 command3 ... commandN outfile
./pipex_bonus here_doc LIMITER command1 command2 ... commandN outfile
```
