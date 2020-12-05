/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 18:37:39 by ybolles           #+#    #+#             */
/*   Updated: 2018/10/18 20:25:43 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int i;

	i = 0;
	if (s == NULL || f == NULL)
		return ;
	if (s != NULL)
	{
		while (*s)
		{
			f(i, &*s);
			s++;
			i++;
		}
	}
}
