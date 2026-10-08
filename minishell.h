/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 12:56:50 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 12:56:50 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
// ======================================================== //
//						CONSTANTS							//
// ======================================================== //
# define _XOPEN_SOURCE 600
// colors
// TODO: add prefix to color constants
# define RESET      "\033[0m"
# define BLACK      "\033[30m"
# define RED        "\033[31m"
# define GREEN      "\033[32m"
# define YELLOW     "\033[33m"
# define BLUE       "\033[34m"
# define MAGENTA    "\033[35m"
# define CYAN       "\033[36m"
# define WHITE      "\033[37m"
# define BOLD       "\033[1m"
# define BBLACK     "\033[30;1m"
# define BRED       "\033[31;1m"
# define BGREEN     "\033[32;1m"
# define BYELLOW    "\033[33;1m"
# define BBLUE      "\033[34;1m"
# define BMAGENT    "\033[35;1m"
# define BCYAN      "\033[36;1m"
# define BWHITE     "\033[37;1m"
// prompt colors (\001 \002 = non printing chars for readline)
# define P_RESET    "\001\033[0m\002"
# define P_GREEN    "\001\033[32m\002"
# define P_BGREEN   "\001\033[32;1m\002"
# define P_BBLUE    "\001\033[34;1m\002"
// token
# define TK_BLANK_NAME "TK_BLANK"
# define TK_TAB_VAL '\t'
# define TK_SPACE_VAL ' '
# define TK_SQUOTE_NAME "TK_SQUOTE"
# define TK_SQUOTE_VAL '\''
# define TK_DQUOTE_NAME "TK_DQUOTE"
# define TK_DQUOTE_VAL '\"'
# define TK_PIPE_NAME "TK_PIPE"
# define TK_PIPE_VAL '|'
# define TK_REDIR_IN_NAME "TK_REDIR_IN"
# define TK_REDIR_IN_VAL '<'
# define TK_REDIR_OUT_NAME "TK_REDIR_OUT"
# define TK_REDIR_OUT_VAL '>'
# define TK_WORD_NAME "TK_WORD"
# define TK_METACHARS " \t\'\"|<>"
// ======================================================== //
//						DEPENDENCIES						//
// ======================================================== //
# include "./libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_signal;
// ======================================================== //
//						STRUCTURES							//
// ======================================================== //
typedef struct s_context	t_context;
typedef struct s_token		t_token;
typedef struct s_word		t_word;
typedef struct s_heredoc	t_heredoc;
typedef struct s_redir		t_redir;
typedef struct s_cmd		t_cmd;
typedef struct s_exp		t_exp;
enum e_structure_type
{
	T_NULL_TYPE,
	T_CONTEXT_TYPE,
	T_TOKEN_TYPE,
	T_CMD_TYPE,
};
// fourre tout
struct s_context
{
	char	*prompt;
	size_t	line_len;
	char	*line;
	t_token	*current_token;
	int		token_cnt;
	t_list	*token_lst;
	int		cmd_cnt;
	t_list	*cmd_lst;
	int		envp_cnt;
	t_list	*envp_lst;
	int		exit_status;
	int		is_child;
	int		heredoc_cnt;
	int		saved_fd[2];
};
// token
typedef enum e_token_type
{
	TK_BLANK,
	TK_SQUOTE,
	TK_DQUOTE,
	TK_PIPE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_WORD,
	TK_END,
}	t_token_t;
struct s_token
{
	t_token_t	type;
	size_t		start;
	size_t		len;
};
// word
struct s_word
{
	char	*str;
	int		flags;
};
enum e_word_flags
{
	W_NULL = 1 << 0,
	W_COMMAND = 1 << 1,
	W_SQUOTE = 1 << 2,
	W_DQUOTE = 1 << 3,
	W_WORD = 1 << 4,
	W_EXPAND = 1 << 5,
};
// redir
typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC,
}	t_redir_t;
typedef union u_redir_val
{
	char	*path;
	char	*delim;
}	t_redir_v;
struct s_redir
{
	int			fd;
	int			mode;
	t_redir_t	type;
	t_redir_v	val;
	int			heredoc_fd;
};
// cmd
struct s_cmd
{
	int		status;
	int		redir_cnt;
	t_list	*redir_in_lst;
	t_list	*redir_out_lst;
	int		argc;
	t_list	*argv;
	char	**av;
	int		expanded;
	long	arg_end;
};
// expansion
struct s_exp
{
	t_context	*ctx;
	t_list		*fields;
	char		*buf;
	int			started;
	int			split;
};
// ======================================================== //
//						PROMPTING							//
// ======================================================== //
void		print_welcome(t_context *ctx);
char		*get_prompt(void);
char		*get_hostname(void);
char		*build_prompt(t_context *ctx);
char		*join_and_free(char *s1, char *s2);
// signal.c
void		create_signal(void);
void		handle_signal(int sig);
void		signal_exec(void);
void		signal_default(void);
void		signal_heredoc(void);
// errors.c
void		error(char *command, char *error);
void		error_arg(char *cmd, char *arg, char *msg);
// free.c
void		free_array(char **array);
void		delete_arg(void *content);
void		delete_redir(void *content);
void		delete_cmd(void *content);
void		free_line(t_context *ctx);
// ======================================================== //
//						TOKENIZE							//
// ======================================================== //
// token.c
t_token_t	get_token_type(char token_val);
char		*get_token_name(t_token_t type);
void		print_token(void *content);
size_t		quote_len(char *quote_start, t_token_t quote_type);
size_t		token_len(char *token_start, t_token_t type);
// tokenize.c
void		delete_token(void *token);
void		token_lst_add_back(t_context *ctx, t_token *token);
t_token		*build_token_from(char *line, size_t token_start);
int			tokenize(t_context *ctx);
// ======================================================== //
//						PARSING								//
// ======================================================== //
// ft_sublst.c
t_list		*ft_sublst(t_list **lst, int start, int len);
// parse_check.c
int			check_syntax(t_context *ctx);
// parse_argv.c
int			init_argv(t_cmd *cmd, t_list **token_lst, char *line);
// parse_redir_utils.c
int			add_redir(t_cmd *cmd, t_redir *redir, t_token *token);
int			absorb_adjacent(t_redir *redir, t_list **node, char *line);
// parse_init_redir.c
int			init_redir(t_cmd *cmd, t_list **token_lst, char *line);
// parse_utils.c
int			valid_pipes(t_list *token_lst);
int			valid_redir_syntax(t_list *token_lst);
void		print_word(void *content);
void		print_redir(void *content);
void		print_cmd(void *content);
// parse.c
int			init_cmd_lst(t_context *ctx);
// ======================================================== //
//						EXPANSION							//
// ======================================================== //
// expand.c
t_list		*expand_word(t_context *ctx, char *raw);
t_list		*expand_arg(t_context *ctx, char *raw, int decl);
// expand_utils.c
void		exp_init(t_exp *x, t_context *ctx, int split);
void		exp_push(t_exp *x);
void		exp_add(t_exp *x, char *s, size_t len);
void		exp_val(t_exp *x, char *val, int quoted);
// expand_var.c
void		exp_var(t_exp *x, char *s, size_t *i, int quoted);
// expand_cmd.c
int			expand_cmd(t_context *ctx, t_cmd *cmd);
char		*expand_redir_path(t_context *ctx, t_redir *r);
// input.c
char		*read_input(char *prompt);
// heredoc.c
int			read_heredocs(t_context *ctx);
// heredoc_tmp.c
int			open_tmp(t_context *ctx, int *rfd);
int			tmp_fail(int wfd, int rfd);
// heredoc_utils.c
char		*strip_quotes(char *raw, int *quoted);
char		*expand_heredoc_line(t_context *ctx, char *line);
void		write_line(t_context *ctx, int fd, char *line, int quoted);
void		warn_eof(char *delim);
// ======================================================== //
//						ENVIRONMENT							//
// ======================================================== //
// env_init.c
void		init_env(t_context *ctx, char **envp);
char		**env_to_array(t_context *ctx, int only_set);
// env_utils.c
t_list		*find_env_node(t_context *ctx, char *key);
char		*get_env(t_context *ctx, char *key);
int			set_env_var(t_context *ctx, char *key, char *val);
void		set_env_decl(t_context *ctx, char *key);
void		unset_env(t_context *ctx, char *key);
// env_name.c
size_t		name_len(char *s);
int			is_valid_name(char *s, size_t len);
// ======================================================== //
//						EXECUTION							//
// ======================================================== //
// builtins
int			ft_cd(t_context *ctx, char **av);
int			ft_echo(t_context *ctx, char **av);
int			ft_env(t_context *ctx, char **av);
int			ft_exit(t_context *ctx, char **av);
int			ft_export(t_context *ctx, char **av);
int			ft_pwd(t_context *ctx, char **av);
int			ft_unset(t_context *ctx, char **av);
int			print_export(t_context *ctx);
void		exit_shell(t_context *ctx, int status);
// exec_builtin.c
int			is_builtin(char *name);
int			run_builtin(t_context *ctx, char **av);
// exec_path.c / exec_cmd.c
char		*resolve_command(t_context *ctx, char *name, int *code);
void		exec_external(t_context *ctx, char **av);
// exec_redir.c
int			apply_redirs(t_context *ctx, t_cmd *cmd);
void		close_heredocs(t_context *ctx);
// exec_pipe.c / exec_wait.c / exec.c
void		exec_pipeline(t_context *ctx);
void		wait_all(t_context *ctx, pid_t last);
void		exec_inline(t_context *ctx, t_cmd *cmd);
void		monitor(t_context *ctx);

#endif
