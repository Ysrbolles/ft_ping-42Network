/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 20:24:36 by ybolles           #+#    #+#             */
/*   Updated: 2018/10/17 23:33:25 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	size_t	i;
	char	*src;
	char	*dst;

	dst = (char*)s1;
	src = (char*)s2;
	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		if (src[i] == (char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
