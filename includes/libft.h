/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:27:42 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/04 21:11:02 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

#include <unistd.h>
#include <stdlib.h>

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	*ft_realloc(void *ptr, size_t new_size);
char	**ft_split(char *s, char c);
char	*ft_strcat(char *dest, const char *src);
int		ft_strlen(char *s);
int		ft_strcmp(char *s1, char *s2);
char	*get_next_line(int fd);

#endif