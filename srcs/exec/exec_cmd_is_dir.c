#include "../../inc/minishell.h"

/**
 * @note   check is first argument is a directory
 * @param  cmd: given first argument
 * @retval true or false
*/
bool	cmd_is_dir(char *cmd)
{
	DIR		*dir;
	char	*start_msg;
	char	*err_msg;
	char	*msg;

	start_msg = ft_strdup("minishell: ");
	err_msg = ft_strjoin(cmd, ": Is a directory\n");
	msg = ft_strjoin(start_msg, err_msg);
	dir = opendir(cmd);
	if (dir != NULL)
	{
		closedir(dir);
		ft_putstr_fd(msg, STDERR_FILENO);
		(free(start_msg), free(err_msg), free(msg));
		return (true);
	}
	(free(start_msg), free(err_msg), free(msg));
	return (closedir(dir), false);
}
