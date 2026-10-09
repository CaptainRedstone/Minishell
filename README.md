*This project has been created as part of the 42 curriculum by ethrober, aforcada*

# Minishell

## Description

Minishell is a small shell written in C: our own little Bash. The goal of the
project is to understand how a shell works under the hood: processes
(`fork`, `execve`, `wait`), file descriptors (`pipe`, `dup2`), signals and
parsing.

Features:

- Prompt, command history (readline) and a non interactive mode
  (`./minishell < script`: no prompt, same output as bash).
- Execution of commands found through `PATH`, or given with a relative or
  absolute path.
- Quotes: `'...'` (nothing is interpreted) and `"..."` (only `$` is
  interpreted). `\` and `;` are not interpreted.
- Redirections `<`, `>`, `>>` and heredoc `<<` (the heredoc is not added to
  the history).
- Pipes `|`.
- Environment variables (`$VAR`), `$?`, and word splitting of unquoted
  expansions.
- `ctrl-C`, `ctrl-D` and `ctrl-\` behave like in bash (interactive mode).
- Builtins: `echo -n`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.

### Overview of the code (`src/`)

| Step | Files |
| --- | --- |
| Reading the line | `main.c`, `input.c`, `prompt.c`, `signal.c` |
| Tokenizing | `token.c`, `tokenize.c` |
| Syntax check + building the commands | `parse_check.c`, `parse.c`, `parse_argv.c`, `parse_init_redir.c`, `parse_redir_utils.c` |
| Expansion (`$VAR`, `$?`, quote removal, word splitting) | `expand.c`, `expand_utils.c`, `expand_var.c`, `expand_cmd.c` |
| Heredocs | `heredoc.c`, `heredoc_tmp.c`, `heredoc_utils.c` |
| Environment | `env_init.c`, `env_utils.c`, `env_name.c` |
| Execution | `exec.c`, `exec_pipe.c`, `exec_wait.c`, `exec_redir.c`, `exec_path.c`, `exec_cmd.c`, `exec_builtin.c` |
| Builtins | `echo.c`, `cd.c`, `pwd.c`, `export.c`, `export_print.c`, `unset.c`, `env.c`, `exit.c` |

### Technical choices

- **Raw words.** The parser keeps each word exactly as typed (quotes
  included). Quotes are removed and variables expanded later, right before the
  command runs (`expand_cmd`)
- **Execution.** A single builtin runs in the shell process (needed for `cd`,
  `export`, `unset`, `exit`), with stdin/stdout saved and restored around its
  redirections. Everything else runs in a child process, connected to the
  next one by a pipe. The status of a pipeline is the one of its last command.
- **Heredocs** are all read before anything runs, by a child process (so
  `ctrl-C` can cancel them). The content goes into a temporary file that is
  unlinked immediately: only the open descriptor remains.
- **Signals.** One global variable, `g_signal`, which only stores the signal
  number. While children run, the shell ignores `SIGINT`/`SIGQUIT`; children
  use the default behavior. A child killed by a signal gives `128 + signal`.
- **Environment** is a linked list of `KEY=VALUE` strings owned by the shell
  (so `unset PATH` really disables the `PATH` lookup).

## Instructions

Requirements: a C compiler (`cc`), `make` and the `readline` library
(`libreadline-dev` on Debian/Ubuntu).

```sh
make          # builds ./minishell (libft is built first)
./minishell   # run it
make clean    # remove object files
make fclean   # remove object files and the binary
make re       # fclean + all
```

For testing with valgrind :

```sh
valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=./ignore_readline_leaks.supp --track-fds=yes ./minishell
```

Examples (inside minishell):

```sh
echo "hello $USER" | cat -e > out.txt
cat << END | grep two
one
two
END
export A="a b"
echo $A
```

## Resources

- `man bash`, `man 2 fork execve pipe dup2 waitpid sigaction`, `man 3 readline`
- GNU Bash Reference Manual: <https://www.gnu.org/software/bash/manual/>
- The Open Group, *Shell Command Language* (POSIX):
  <https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html>
- Behavior was compared systematically with `bash` (stdout and exit status).

### Use of AI

AI was used as a support tool, and all its output was reviewed, tested and understood before being kept:

- **README**: AI helped draft and structure this README from the project subject.
- **Concepts**: AI was used to clarify concepts such as data races, deadlocks and the dining philosophers problem.
- **Makefile**: Adapting the Makefile to the final structure of the project.
