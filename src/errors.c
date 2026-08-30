#include "../minishell.h"

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
