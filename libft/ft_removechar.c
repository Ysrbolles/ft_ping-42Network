/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_removechar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 03:59:11 by ybolles           #+#    #+#             */
/*   Updated: 2018/10/15 21:24:03 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_removechar(char *str)
{
	int		i;
	int		j;
	char	*dest;
	int		l;

	i = 0;
	j = 0;
	l = ft_strlen(str);
	dest = (char*)malloc(sizeof(char) * l);
	while (str[i] != '\0')
	{
		if ((str[i] >= 'a' && str[i] <= 'z') ||
				(str[i] >= 'A' && str[i] <= 'Z'))
		{
			dest[j] = str[i];
			j++;
		}
		i++;
	}
	dest[j] = '\0';
	return (dest);
}
