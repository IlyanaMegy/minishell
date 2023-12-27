#include "../inc/minishell.h"

/**
 * @note   replace content of existing var in environment
 * @param  name: variable name
 * @param  content: variable content
 */
void	replace_var_in_env(char *name, char *content, int *append)
{
	t_env	*e;
	char	*tmp;

	e = g_minishell.env;
	while (ft_strcmp(e->name, name))
		e = e->next;
	if (e && e->content && *append)
	{
		tmp = ft_strjoin(e->content, content);
		free(e->content);
		e->content = ft_strdup(tmp);
		free(tmp);
		e->print_it = 1;
		return ;
	}
	if (e && e->content)
		free(e->content);
	if (e && content)
		e->content = ft_strdup(content);
	else if (e)
		e->content = ft_strdup("");
	e->print_it = 1;
}

/**
 * @note   get variable content from the environment
 * @param  var_name: variable name
 * @retval content is yes, NULL is no variable with that name
 */
char	*get_var_content_from_env(char *var_name)
{
	t_env	*e;

	e = g_minishell.env;
	while (e)
	{
		if (!ft_strcmp(e->name, var_name))
			return (e->content);
		e = e->next;
	}
	return (NULL);
}

/**
 * @note   is this variable already in the environment ?
 * @param  var_name: variable name
 * @retval 1 is yes, 0 is no
 */
int	var_is_in_env(char *var_name)
{
	t_env	*e;

	e = g_minishell.env;
	while (e)
	{
		if (!ft_strcmp(e->name, var_name))
			return (1);
		e = e->next;
	}
	return (0);
}

/**
 * @note   get next sorted var
 * @param  head: pointer to first element of the list
 * @param  node: element to compare to
 * @retval None
 */
void	sorted_var(t_env **head, t_env *node)
{
	t_env	tmp;
	t_env	*curr;

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
 * @param  head: pointer to first element of the list
 * @retval None
 */
void	get_sorted_env(t_env **head)
{
	t_env	*res;
	t_env	*tmp;
	t_env	*curr;

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
