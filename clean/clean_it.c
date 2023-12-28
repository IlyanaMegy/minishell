#include "../inc/minishell.h"

/**
 * @note   clean the env list
 * @retval NULL env
*/
t_env	*clean_env(void)
{
	t_env	*e;
	t_env	*tmp;

	e = single_env(NULL, 0);
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
	return ( NULL);
}
