#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"

void	error(char *command, char *error)
{
	printf(BRED "MiniShell"
		BWHITE " > "
		BRED "%s"
		BWHITE " > "
		BRED "%s\n"
		RESET,
		command,
		error);
}
