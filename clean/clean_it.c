#include "../inc/minishell.h"

/**
 * @note   clean the env list
 * @param  env: environment list
 * @retval None
*/
void	clean_env(t_env *env)
{
	t_env_var	*e;
	t_env_var	*temp;

	e = env->f_var;
	if (e == NULL)
		return ;
	while (e != NULL)
	{
		temp = e->next;
		free(e->content);
		free(e->name);
		free(e);
		e = temp;
	}
	env = NULL;
}
