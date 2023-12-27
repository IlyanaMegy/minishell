#include "../inc/minishell.h"

/**
 * @note   clean the env list
 * @param  env: environment list
 * @retval None
*/
void	clean_env()
{
	t_env	*e;
	t_env	*tmp;

	e = g_minishell.env;
	if (e == NULL)
		return ;
	while (e != NULL)
	{
		tmp = e->next;
		if (e->content != NULL)
			free(e->content);
		free(e->name);
		free(e);
		e = tmp;
	}
	g_minishell.env = NULL;
}
