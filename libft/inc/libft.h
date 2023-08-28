/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:33:25 by pmessett          #+#    #+#             */
/*   Updated: 2023/07/10 23:54:35 by pmessett            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* --- Dependencies Libs --- */

# include <fcntl.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* --- Macro Variables --- */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

# define HEX_UP "0123456789ABCDEF"
# define HEX_LOW "0123456789abcdef"

/* --- Linked list struct --- */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

/* --- Utils functions --- */

int					ft_str_empty(char *s);
int					ft_str_is_num(char *s);
int					ft_str_isspace(char *s);
int					ft_isalpha(int c);
int					ft_isnum(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isspace(char c);
int					ft_isdir(char *s);
int					ft_toupper(int c);
int					ft_tolower(int c);

/* --- String functions --- */

char				*ft_strdup(const char *s);
size_t				ft_strlen(const char *s);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_multi_strjoin(const char *delimiter, ...);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				**ft_split(char const *s, char c);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);

/* --- Memory functions --- */

void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				free_matrix(char **matrix);

/* --- Integers functions --- */

int					ft_atoi(const char *nptr);
char				*ft_itoa(int n);

/* --- FD functions --- */

void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbr_base_fd(int nbr, char *base, int fd);
char				*get_next_line(int fd);

/* --- Printf functions --- */

int					ft_printf(const char *s, ...);
void				ft_putchar(char c, unsigned int *size);
void				ft_putstr(char *s, unsigned int *size);
void				ft_putnbr(int n, unsigned int *size);
void				ft_putnbr_base(unsigned int n, char *base,
						unsigned int *size);
void				ft_putunsnbr(unsigned int n, unsigned int *size);

/* --- Linked list functions --- */

void				free_list(t_list **list);
t_list				*ft_find_head(t_list *list);
t_list				*ft_add_new_node(void *content);
void				ft_add_tail(t_list **list, t_list *new_node);
t_list				*find_tail(t_list *list);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
int					ft_list_size(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
void				free_list(t_list **list);

#endif
