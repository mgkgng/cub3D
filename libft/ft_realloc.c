/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:47:52 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/09 13:37:01 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* it's not the real realloc, but I just named it as. */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t new_size)
{
	size_t	current_size;
	void	*new_ptr;

	if (!ptr)
		return (malloc(new_size));	
	current_size = ft_strlen((char *) ptr);
	if (current_size > new_size)
		return (ptr);
	new_ptr = malloc(new_size);
	new_ptr = ft_memcpy(new_ptr, ptr, current_size);
	free(ptr);
	return (new_ptr);
}
