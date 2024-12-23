/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:26:51 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/11 20:35:41 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_formatter	t_formatter;
typedef struct s_list		t_list;

struct						s_formatter
{
	ssize_t					n;
	int						err;
	t_list					*flags;
};

struct						s_list
{
	char					*val;
	struct s_list			*next;
};

int							ft_printf(char const *fmt, ...);
int							ft_display_formatted(char const *fmt,
								t_list *stats);
void						ft_parse_flags(char const *fmt, va_list args,
								t_formatter *fmtr);
void						ft_count_flags(char const *fmt, t_formatter *flags);
int							ft_char_in_s(char c, char const *s);
void						ft_strrev(char *str);
char						*va_list_parser(char flag, va_list args);
void						*ft_calloc(size_t nmemb, size_t sz);
void						*ft_memcpy(void *d, void const *s, size_t sz);
int							ft_putchar_fd(char const c, int fd);
int							ft_putstr_fd(char const *s, int fd);
char						*ft_strdup(char const *s);
char						*ft_strjoin(char const *s1, char const *s2);
size_t						ft_strlen(char const *s);
int							ft_strncmp(char const *s1, char const *s2,
								size_t n);
char						*ft_itoa(int n);
char						*ft_itoa_unsigned(uint32_t n);
char						*ft_ltoh(unsigned long n, bool upper);
t_list						*ft_lstnew(char *val);
void						ft_lstclear(t_list **lst, void (*del)(void *));
void						ft_lstadd_back(t_list **lst, t_list *new);
#endif