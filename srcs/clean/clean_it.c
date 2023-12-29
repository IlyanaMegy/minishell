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
	return ( NULL);
}
