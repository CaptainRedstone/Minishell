#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"

char	*get_input(char *line, char *pos_i)
{
	char	*input;

	if (pos_i == line)
		input = ft_strdup("");
	else
		input = ft_substr(line, 0, pos_i - line - 1);
	return (input);
}

void	handle_quote(char *line, char *dest, int *i, int *j)
{
	char	quote;

	quote = line[*i];
	dest[(*j)++] = line[(*i)++];
	while (line[*i] && line[*i] != quote)
		dest[(*j)++] = line[(*i)++];
	if (line[*i] == quote)
		dest[(*j)++] = line[(*i)++];
}

int	count_args(char *s)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break ;
		count++;
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			if (s[i])
				i++;
		}
		else
		{
			while (s[i] && s[i] != ' ')
				i++;
		}
	}
	return (count);
}

size_t arg_len(char *s, int start)
{
    int     i;
    char    quote;

    i = start;

    if (s[i] == '\'' || s[i] == '"')
    {
        quote = s[i++];
        while (s[i] && s[i] != quote)
            i++;
        if (s[i])
            i++;
    }
    else
    {
        while (s[i] && s[i] != ' ')
            i++;
    }
    return (i - start);
}
