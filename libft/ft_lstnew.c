/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 22:06:37 by ybolles           #+#    #+#             */
/*   Updated: 2018/10/14 05:08:49 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *ls;

	if (!(ls = (void*)malloc(sizeof(t_list))))
		return (NULL);
	ls->next = NULL;
	if (content == NULL)
	{
		ls->content = NULL;
		ls->content_size = 0;
		return (ls);
	}
	if (!(ls->content = (t_list*)malloc((content_size) * sizeof(t_list))))
		return (NULL);
	ls->content = ft_memmove(ls->content, content, content_size);
	ls->content_size = content_size;
	return (ls);
}
