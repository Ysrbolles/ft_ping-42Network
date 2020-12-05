/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 17:13:33 by ybolles           #+#    #+#             */
/*   Updated: 2018/10/14 18:31:33 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list *n;

	while (*alst)
	{
		n = (*alst)->next;
		ft_lstdelone(alst, del);
		*alst = n;
	}
}
