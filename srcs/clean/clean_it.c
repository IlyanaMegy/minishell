#include "../../inc/minishell.h"

/**
 * @note   clean the env list
 * @param  e:	environment list to clear
 * @retval NULL env
*/
t_env	*clean_env(t_env *e)
{
	t_env	*tmp;

	if (e == NULL)
		return (NULL);
	while (e != NULL)
	{
		tmp = e->next;
		if (e->content != NULL)
			free(e->content);
		free(e->name);
		free(e);
		e = tmp;
	}
	e = NULL;
	return (e);
}

void	free_tab(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	return ;
}

void	clean_program(char **cmd)
{
	free_tab(cmd);
	clean_env(single_env(NULL, GET));
	rl_clear_history();
	// !	clear everything malloc
}
