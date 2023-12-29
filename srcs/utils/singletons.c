#include "../../inc/minishell.h"

/**
 * @note   update, clear or return current t_env linked list
 * @param  env: environment list
 * @param  mode: ADD - GET - RM
 * @retval return current t_env list
*/
t_env	*single_env(t_env *env, int mode)
{
	static t_env	*single_env = NULL;

	if (mode == ADD)
		single_env = env;
	else if (mode == RM)
	{
		single_env = clean_env(env);
		return (single_env);
	}
	else if (mode == GET)
		return (single_env);
	return (single_env);
}

/**
 * @note   update or return current exit status
 * @param  exit_s: exit status 
 * @param  mode: ADD or GET
 * @retval return current exit status
*/
int	single_exit_s(int exit_s, int mode)
{
	static int	single_exit_s = 0;

	if (mode == ADD)
		single_exit_s = exit_s;
	if (mode == GET)
		return (single_exit_s);
	return (single_exit_s);
}

/**
 * @note   recursively copy t_env linked list to new t_env list
 * @param  src: t_env linked list to copy
 * @retval return new t_env list
*/
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
