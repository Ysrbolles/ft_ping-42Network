/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:18:08 by ybolles           #+#    #+#             */
/*   Updated: 2018/10/17 21:21:24 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*dest;
	size_t			i;

	i = 0;
	dest = str;
	while (i < n)
	{
		dest[i] = c;
		i++;
	}
	return (dest);
}
