/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:33:35 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/09 13:36:19 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char	*res;

	if (!s)
		return (NULL);
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		res[i] = (char) s[start + i];
		i++;
	}
	return (res);
}

static int	count_size(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = -1;
	count = 0;
	while (s[++i])
		if (s[i] == c && s[i + 1] && s[i + 1] != c)
			count++;
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		start;
	int 	len;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (count_size(s, c) + 1));
	if (!res)
		return (NULL);
	start = 0;
	i = 0;
	while (s[start])
	{
		while (s[start] == c)
			start++;
		len = 0;
		while (s[start + len] && s[start + len] != c)
			len++;
		if (s[start])
			res[i++] = ft_substr(s, start, len);
		start += len;
	}
	res[i] = NULL;
	return (res);
}