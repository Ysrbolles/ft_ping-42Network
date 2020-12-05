/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 23:24:35 by ybolles           #+#    #+#             */
/*   Updated: 2018/10/20 23:26:07 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcmp2(const char *s1, const char *s2)
{
	unsigned char *str1;
	unsigned char *str2;

	str1 = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	while (*str2)
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		str1++;
		str2++;
	}
	return (0);
}

char		*ft_strnstr(const char *find, const char *tofind, size_t len)
{
	size_t	i;

	if (*tofind == '\0')
		return ((char*)find);
	i = ft_strlen(tofind);
	while (*find && len)
	{
		if (*find == *tofind)
		{
			if (ft_strcmp2(find, tofind) == 0)
			{
				if (i > len + 1)
					break ;
				return ((char *)find);
			}
		}
		find++;
		len--;
	}
	return (0);
}
