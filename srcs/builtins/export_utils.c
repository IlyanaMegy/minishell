#include "../../inc/minishell.h"

/**
 * @note   replace content of existing var in environment
 * @param  name: variable name
 * @param  content: variable content
 */
void	replace_var_in_env(char *name, char *content, int *append)
{
	t_env	*e;
	char	*tmp;

	e = single_env(NULL, GET);
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

	e = single_env(NULL, GET);
	while (e)
	{
		if (!ft_strcmp(e->name, var_name))
			return (e->content);
		e = e->next;
	}
	return (NULL);
}

/**
 * @note   simply display environment, print_it == 0 vars included
 * @retval None
 */
void	display_export(void)
{
	t_env	*e;
	t_env	*dirty_e;

	dirty_e = copy_my_lst(single_env(NULL, GET));
	if (dirty_e != NULL)
	{
		e = get_sorted_env(&dirty_e);
		while (e)
		{
			if (!(strcmp(e->name, "_")) && strlen(e->name) == 1)
				ft_printf("");
			else
				ft_printf("export %s=\"%s\"\n", e->name, e->content);
			e = e->next;
		}
		clean_env(dirty_e);
	}
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
t_env	*get_sorted_env(t_env **head)
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
	return (res);
}
