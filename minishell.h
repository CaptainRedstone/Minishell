/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 10:43:09 by aforcada          #+#    #+#             */
/*   Updated: 2026/09/16 15:59:09 by aforcada         ###   ########.fr       */
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
# include <sys/wait.h>
# include <unistd.h>
// ======================================================== //
//						STRUCTURES							//
// ======================================================== //
// TODO: remove t_commmand and dependencies
typedef struct s_context	t_context;
typedef struct s_token		t_token;
typedef struct s_command	t_command;
typedef struct s_word		t_word;
typedef struct s_heredoc	t_heredoc;
typedef struct s_redir		t_redir;
typedef struct s_cmd		t_cmd;
enum e_structure_type
{
	T_NULL_TYPE,
	T_CONTEXT_TYPE,
	T_TOKEN_TYPE,
	T_CMD_TYPE,
};
// to be removed
struct s_command
{
	char	*input;
	char	*output;
	char	*command_line;
	char	**commands;
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
};
// ======================================================== //
//						PROMPTING							//
// ======================================================== //
void		print_welcome(void);
char		*get_prompt(void);
char		*get_hostname(void);
char		*build_prompt(void);
char		*join_and_free(char *s1, char *s2);
void		create_signal(void);
void		handle_signal(int sig);
void		error(char *command, char *error);
void		free_array(char **array);
void		free_struct(t_command command);
void		print_command(t_command command);
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
//						EXECUTION							//
// ======================================================== //
void		execute_command(char *line, char **envp);
/* void		ft_cd(t_command command);
void		ft_env(t_command command, char **envp);
void		ft_pwd(t_command command);
void		ft_echo(t_command command);
void		ft_exit(t_command command);
void		ft_color(t_command command);
void		ft_executable(t_command command); */
#endif
