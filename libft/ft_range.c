/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 20:38:18 by ybolles           #+#    #+#             */
/*   Updated: 2018/10/15 21:06:23 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_range(int min, int max)
{
	int *t;

	if (min >= max)
	{
		t = NULL;
		return (t);
	}
	if (!(t = malloc(sizeof(int) * (max - min))))
		return (NULL);
	while (max >= min)
	{
		t[max - min - 1] = max - 1;
		max--;
	}
	return (t);
}
