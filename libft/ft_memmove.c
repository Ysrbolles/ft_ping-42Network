/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 19:04:31 by ybolles           #+#    #+#             */
/*   Updated: 2018/10/19 00:12:06 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	char	*src;
	char	*dest;
	size_t	i;

	i = -1;
	src = (char*)s2;
	dest = (char*)s1;
	if (src < dest)
		while ((int)--n >= 0)
			*(dest + n) = *(src + n);
	else
		while (++i < n)
			*(dest + i) = *(src + i);
	return (dest);
}
