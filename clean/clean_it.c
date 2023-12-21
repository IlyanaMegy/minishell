#include "../inc/minishell.h"

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
	// free(env);
	env = NULL;
}