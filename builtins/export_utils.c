#include "../inc/minishell.h"

/**
 * @note   get next sorted var
 * @param  **head: 
 * @param  *node: 
 * @retval None
*/
void	sorted_var(t_env_var **head, t_env_var *node)
{
	t_env_var	tmp;
	t_env_var	*curr;

	curr = &tmp;
	tmp.next = *head;
	while (curr->next != NULL && ft_strcmp(curr->next->name, node->name) < 0)
		curr = curr->next;
	node->next = curr->next;
	curr->next = node;
	*head = tmp.next;
}

/** 
 * @note   get a alphabetically sorted env
 * @param  t_env** head: 
 * @retval 
*/
void	get_sorted_env(t_env_var **head)
{
	t_env_var	*res;
	t_env_var	*tmp;
	t_env_var	*curr;

	curr = *head;
	res = NULL;
	while (curr != NULL)
	{
		tmp = curr->next;
		sorted_var(&res, curr);
		curr = tmp;
	}
	*head = res;
}