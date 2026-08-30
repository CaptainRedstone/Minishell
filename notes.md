### parent
- split readline on pipe token '|'
- count number of processes, put result in context
- build sub/child processes in a supervisor/parent process
- 
- in sub process

1. tokenize
1. pipex
1. command struct

### envp

### redirs

- IN (<) cannot have filename which isnt valid path, nothing comes from nowhere right? the error message is as follows
"bash: <filename>: no such file or directory"

- OUT (>) can have filename which arent in current path. As long as it doesnt need to be in a folder which doesnt exist, a file is created if need be.

