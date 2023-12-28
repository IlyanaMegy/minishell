#include "../inc/minishell.h"

t_env	*single_env(t_env *env, int mode)
{
	static t_env *single_env = NULL;
	if (mode == ADD)
		single_env = env;
	else if (mode == RM)
		single_env = clean_env();
	return (single_env);
}

// char **single_env(char **env, int mode)
// {
// 	static t_env *single_env = NULL;

// 	if (mode == ADD)
// 	{
// 		single_env = env;
// 		return single_env;
// 	}
// 	return single_env;
// }

// int var1;
// int	main(int ac, char **av, char **env)
// {
// 	int var2;
// 	single_env(env, ADD);
// 	single_env(NULL, 0);
// }
