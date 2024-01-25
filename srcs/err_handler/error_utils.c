#include "../../inc/minishell.h"

/**
 * @note   get only two first characters of cmd
 * @param  cmd: given command
 * @retval two first char
*/
char	*two_first_char(char *cmd)
{
	char	*opt;

	opt = malloc(sizeof(char) * 3);
	opt[0] = cmd[0];
	opt[1] = cmd[1];
	opt[2] = '\0';
	return (opt);
}
