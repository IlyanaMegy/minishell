#include "../../inc/minishell.h"

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
