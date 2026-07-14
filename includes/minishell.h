#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_command
{
	char	*input;
	char	*output;
	char	*command_line;
	char	**commands;
}			t_command;

/**
 * @brief	Context structure
 * 
 * @param	prompt[char*]		string prompt before input
 * @param	line[char*]			output of `readline(prompt)` 
 * @param	line_len[size_t]	length of `line`
 * @param	token_lst[t_list*]	list of tokens, see `t_token`
 * @param	token_cnt[int]		number of elements in `token_lst`
 */
typedef struct s_context
{
	char	*prompt;
	char	*line;
	size_t	line_len;
	t_list	*token_lst;
	int		token_cnt;
}	t_context;

void		print_welcome(void);

char		*get_prompt(void);
char		*get_hostname(void);
char		*build_prompt(void);
char		*join_and_free(char *s1, char *s2);

int 		count_args(char *s);
char		*parse_line(char *line);
size_t		arg_len(char *s, int start);
char		*get_input(char *line, char *pos_i);
void		execute_command(char *line, char **envp);
t_command	parse_command(char *line, t_command command);
t_command	parse_input_output(char *line, t_command command);

/* void		ft_cd(t_command command);
void		ft_env(t_command command, char **envp);
void		ft_pwd(t_command command);
void		ft_echo(t_command command);
void		ft_exit(t_command command);
void		ft_color(t_command command);
void		ft_executable(t_command command); */

void		create_signal(void);
void		handle_signal(int sig);

void		error(char *command, char *error);

void		free_array(char **array);
void		free_struct(t_command command);

void		print_command(t_command command);

#endif