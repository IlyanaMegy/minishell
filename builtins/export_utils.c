#include "../inc/minishell.h"

/**
 * @note   print in fd_out export error
 * @param  arg: shitty argument
 * @retval exit error
*/
int	print_export_err_msg(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

/**
 * @note   replace content of existing var in environment
 * @param  env: environment list
 * @param  name: variable name
 * @param  content: variable content
*/
void	replace_var_in_env(t_env *env, char *name, char *content, int *append)
{
	t_env_var	*e;
	char		*tmp;

	e = env->f_var;
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
 * @note   is this var already in the environment ?
 * @param  env: environment list
 * @param  var_name: variable name
 * @retval 1 is yes, 0 is no
*/
int	var_is_in_env(t_env *env, char *var_name)
{
	t_env_var	*e;

	e = env->f_var;
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
 * @param  head: pointer to first element of the list
 * @retval None
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
