#include "../../inc/minishell.h"

/**
 * @note	get the linked list's size 
 * @param 	lst: linked list to study
 * @retval	the size obviously...
*/
int	ms_lstsize(t_env *lst)
{
	size_t	count;
	t_env	*clone;

	clone = lst;
	count = 0;
	while (clone)
	{
		count++;
		clone = clone->next;
	}
	return (count);
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

char **env_to_tab(t_env *env)
{
	
}