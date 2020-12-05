/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 03:35:46 by ybolles           #+#    #+#             */
/*   Updated: 2018/10/20 22:14:57 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*n;
	t_list	*first;

	first = NULL;
	if (lst == NULL)
		return (NULL);
	n = ft_lstnew(f(lst)->content, f(lst)->content_size);
	first = n;
	while (lst->next)
	{
		n->next = ft_lstnew(f(lst->next)->content, f(lst->next)->content_size);
		n = n->next;
		lst = lst->next;
	}
	return (first);
}
