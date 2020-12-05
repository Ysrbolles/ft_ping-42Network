/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 14:08:03 by ybolles           #+#    #+#             */
/*   Updated: 2018/10/18 05:15:00 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *str;
	char co;

	str = (char *)s;
	co = c;
	while (*str)
	{
		if (*str == co)
			break ;
		str++;
	}
	if (*str == co)
		return (str);
	return (NULL);
}
