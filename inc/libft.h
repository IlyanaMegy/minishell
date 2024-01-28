/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:34:32 by ilymegy           #+#    #+#             */
/*   Updated: 2023/12/13 16:34:37 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>

# ifndef T_LIST
#  define T_LIST

typedef struct s_list
{
	struct s_list	*next;
	void			*content;
}	t_list;

typedef struct s_ps
{
	struct s_ps	*next;
	struct s_ps	*prev;
	int			content;
	int			idx;
}	t_ps;

# endif
// LIBFT
int					ft_atoi_base(const char *str, const char *base,
						size_t len_base);
long int			ft_atoi(const char *nptr);
long				ft_atol(const char *nptr);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_free_strs(char **strs, int size);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_ischarset(int c, const char *charset);
int					ft_isdigit(int c);
bool				ft_isdelimiter(char *delimiter, char *str);
int					ft_islower(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_isupper(int c);
int					ft_isnumber(char *s);
int					ft_isnullstr(char c, int quotes);
char				*ft_itoa_base(int n, const char *base, size_t len_base);
char				*ft_itoa(int n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
size_t				ft_nbrlen(int n);
size_t				ft_nbrlen_base(int n, size_t len_base);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(char *s);
char				**ft_split(char *s, char c);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strchr(const char *s, int c);
size_t				ft_strclen(const char *s, const char *charset);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dest, char *src);
char				*ft_strdup(const char *s1);
char				*ft_strndup(const char *s1, int n);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_n_free(char *s1, char *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(char *str1, char *str2, size_t n);
int					ft_strnsame(char const *s1, char const *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strsjoin(char **strs, char *sep);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				print_list(t_list *mylist);

// PRINTF
int					ft_printf(const char *str, ...);
int					search_str(const char *string, int searchedChar);
char				*p_nbr(int nbr);
char				*p_uint(unsigned int n, char format);
int					p_char(char c);
int					p_str(char *str, int *res_l);
int					p_ptr(unsigned long long ptr);

// GNL
# define BUFFER_SIZE 42

char				*get_next_line(int fd);

t_ps				*ft_pslstnew(int content);
void				ft_pslstadd_front(t_ps **lst, t_ps *new);
int					ft_pslstsize(t_ps *lst);
t_ps				*ft_pslstlast(t_ps *lst);
void				ft_pslstadd_back(t_ps **lst, t_ps *new);
void				ft_pslstdelone(t_ps *lst, void (*del)(int));
void				ft_pslstclear(t_ps **lst);
void				ft_pslstiter(t_ps *lst, void (*f)(int));
void				ft_pslstiter_reverse(t_ps *lst, void (*f)(int));
t_ps				*ft_pslstmap(t_ps *lst, int (*f)(int));

void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstadd_front(t_list **alst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
void				ft_list_remove_if(t_list **begin_list,
						void *data_ref, int (*cmp)());
#endif
