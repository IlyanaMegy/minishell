#include "../inc/minishell.h"

t_env	*single_env(t_env *env, int mode)
{
	static t_env	*single_env = NULL;
	if (mode == ADD)
		single_env = env;
	else if (mode == RM)
		single_env = clean_env(env);
	return (single_env);
}

t_env	*copy_my_lst(t_env *src)
{
	t_env	*copy;

	if (src == NULL)
		return (NULL);
	else
	{
		copy = create_var(src->name, src->content, src->print_it);
		if (copy == NULL)
			return (NULL);
		copy->next = copy_my_lst(src->next);
		return (copy);
	}
}
