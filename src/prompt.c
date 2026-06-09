#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"

char	*get_hostname(void)
{
	static char	hostname[256];
	int			fd;
	int			n;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (NULL);
	n = read(fd, hostname, sizeof(hostname) - 1);
	close(fd);
	if (n <= 0)
		return (NULL);
	hostname[n] = '\0';
	if (hostname[n - 1] == '\n')
		hostname[n - 1] = '\0';
	return (hostname);
}

char	*get_prompt(void)
{
	static char	cwd[4096];

	getcwd(cwd, sizeof(cwd));
	return (cwd);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	free(s1);
	return (new);
}

char	*build_prompt(void)
{
	char	*prompt;
	char	cwd[4096];

	getcwd(cwd, sizeof(cwd));
	prompt = ft_strjoin(BGREEN, getenv("USER"));
	prompt = join_and_free(prompt, RESET "@");
	prompt = join_and_free(prompt, BBLUE);
	prompt = join_and_free(prompt, get_hostname());
	prompt = join_and_free(prompt, RESET " : ");
	prompt = join_and_free(prompt, GREEN);
	prompt = join_and_free(prompt, cwd);
	prompt = join_and_free(prompt, RESET " > ");
	return (prompt);
}
