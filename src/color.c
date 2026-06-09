#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"

void	ft_color(char **command)
{
	(void)command;
	printf("\033[32;01m-----------------{FORMAT}-----------------\n");
	printf("\033[37;00mReset\033[00m\t\t: \\033[00m\n");
	printf("\033[37;01mGras\033[00m\t\t: \\033[XX;01m\n");
	printf("\033[37;02mSombre\033[00m\t\t: \\033[XX;02m\n");
	printf("\033[37;03mItalique\033[00m\t: \\033[XX;03m\n");
	printf("\033[37;04mSouligne\033[00m\t: \\033[XX;04m\n");
	printf("\033[37;01m\033[37;04mMulti\033[00m\t\t: "
		"\\033[XX;01m\\033[XX;04m\n");
	printf("\033[32;01m-----------------{COLORS}-----------------\n");
	printf("\033[30;01mGris\033[00m\t\t: \\033[30;XXm\n");
	printf("\033[31;01mRouge\033[00m\t\t: \\033[31;XXm\n");
	printf("\033[32;01mVert\033[00m\t\t: \\033[32;XXm\n");
	printf("\033[33;01mJaune\033[00m\t\t: \\033[33;XXm\n");
	printf("\033[34;01mBleu\033[00m\t\t: \\033[34;XXm\n");
	printf("\033[35;01mRose\033[00m\t\t: \\033[35;XXm\n");
	printf("\033[36;01mCyan\033[00m\t\t: \\033[36;XXm\n");
	printf("\033[37;01mBlanc\033[00m\t\t: \\033[37;XXm\n");
}
