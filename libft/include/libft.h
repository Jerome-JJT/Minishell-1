/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:04:11 by nrossel           #+#    #+#             */
/*   Updated: 2023/05/26 13:11:56 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

/* --------------- Struct node ------------------- */
typedef struct s_node
{
	void			*data;
	int				if_var_env;
	char			*variable;
	char			*valeur;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

/* --------------- list == node ------------------- */
typedef t_node	t_list;

/* --------------- Struct double liste ------------------- */
typedef struct s_dlist
{
	t_node			*head;
	t_node			*tail;
	size_t			len;
}	t_dlist;

/* --------------- Struct liste circulaire ------------------- */
typedef struct s_clist
{
	size_t			len;
	t_list			*head;
}	t_clist;

/* ----------- Fonction Int/Long --------------- */
int			ft_itob(int nbr);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_islower(int c);
int			ft_tolower(int c);
int			ft_islower(int c);
int			ft_toupper(int c);
int			ft_atob(char *str);
int			ft_nbrlen_d(int nbr);
int			ft_nbrlen_exa(int nbr);
long		ft_atoi(const char *str);
int			ft_nbrlen_b(unsigned int nbr);
int			ft_exit(int i, char *error_msg);
int			ft_power(int nbr, unsigned int power);
int			ft_free_2da(char **tab, char *error_msg);
int			ft_btoi(int binaire, t_dlist **trash_lst);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_free_arrays(char *str1, char *str2, char *error_msg);

/* ----------- Fonction Char --------------- */
char		*ft_itoa(int n, t_dlist **trash);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strdup(const char *s1, t_dlist **trash);
char		**ft_split(char const *s, char c, t_dlist **trash);
char		*ft_strmapi(char *s, char (*f)(int, char), t_dlist **trash);
char		*ft_strjoin(char const *s1, char const *s2, t_dlist **trash);
char		*ft_substr(char *s, size_t start, size_t len, t_dlist **trash);
char		*ft_strtrim(char const *s1, char const *set, t_dlist **trash_lst);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);

/* ----------- Fonction Void --------------- */
void		ft_swap(int *a, int *b);
void		ft_putnbr_fd(int n, int fd);
void		ft_bzero(void *s, size_t n);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		*ft_calloc(size_t size, size_t type);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*my_malloc(size_t size, size_t type, t_dlist **trash);
void		ft_striteri(char *s, void (*f) (unsigned int, char *));

/* ----------- Fonction Size_t --------------- */
size_t		ft_strlen(const char *s);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);

/* ----------- Fonction liste simple --------------- */
void		ft_free(void *data);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstiter(t_list *lst, void (*f)(void *));
void		ft_lstadd_front(t_list **lst, t_list *new);
t_list		*ft_lstnew(void *data, t_dlist **trash_lst);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));

/* ----------- Fonction liste double --------------- */
t_node		*ft_pop_back(t_dlist **lst);
t_node		*ft_pop_front(t_dlist **lst);
t_dlist		*ft_dlst_new(t_dlist **trash_lst);
void		ft_dlst_addback(t_dlist **lst, t_node *new);
void		ft_dlst_addfront(t_dlist **lst, t_node *new);
void		ft_dlst_delone(t_node *lst, void (*del)(void *));
void		ft_dlst_clear(t_dlist **dlst, void (*del)(void *));
t_node		*ft_dlst_newcontent(void *data, t_dlist **trash_lst);
void		ft_dlst_addnode(t_dlist **list, t_node *node, size_t position);

/* ----------- Fonction tri --------------- */
void		bubblesort(int	*tab, int size);
void		quicksort(int *tab, int first, int last);

#endif
