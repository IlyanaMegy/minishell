#include "../../inc/minishell.h"

/**
 * @note   handling syntax errors during tokenization and parsing
 * @param  s: wrong token
 * @retval None
*/
void	err_syntax(int err, char *s)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (err == ERR_SYNTAX)
	{
		ft_putstr_fd("syntax error near unexpected token", STDERR_FILENO);
		ft_putstr_fd(" `", STDERR_FILENO);
		ft_putstr_fd(s, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	else if (err == ERR_NOCMD)
	{
		ft_putstr_fd(s, STDERR_FILENO);
		ft_putstr_fd(" : ", STDERR_FILENO);
		ft_putstr_fd("command not found", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

/**
 * @note   error on quotes
 * @param  c: character
 * @retval None
*/
void	err_quote(char c)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `",
					STDERR_FILENO);
	ft_putchar_fd(c, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}