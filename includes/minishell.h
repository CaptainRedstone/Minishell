#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_context	t_context;

typedef struct s_command
{
	char	*input;
	char	*output;
	char	*command_line;
	char	**commands;
}			t_command;

struct s_context
{
	char	*line;
	size_t	line_len;
	char	*prompt;
	t_list	*token_lst;
	int		token_count;
};

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