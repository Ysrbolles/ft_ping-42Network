/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 01:14:32 by ybolles           #+#    #+#             */
/*   Updated: 2018/10/15 01:20:45 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_pow(int nb, int power)
{
	int		cpt;
	int		value;

	cpt = 1;
	value = nb;
	if (power > 0)
		while (cpt++ < power)
			value *= nb;
	else
	{
		if (power == 0)
			value = 1;
		else
			value = 0;
	}
	return (value);
}
