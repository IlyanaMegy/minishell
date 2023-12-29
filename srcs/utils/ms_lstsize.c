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
