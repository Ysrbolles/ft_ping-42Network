/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 09:14:43 by ybolles           #+#    #+#             */
/*   Updated: 2018/10/19 01:16:13 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	char	*str;

	if (s == NULL)
		return (NULL);
	j = ft_strlen(s);
	while (s[j - 1] == ' ' || s[j - 1] == '\t' || s[j - 1] == '\n')
		j--;
	i = -1;
	while (s[++i] == ' ' || s[i] == '\t' || s[i] == '\n')
		j--;
	if (j <= 0)
		j = 0;
	str = (char*)malloc(sizeof(char) * (j + 1));
	if (str == NULL)
		return (NULL);
	s += i;
	i = 0;
	while (i < j)
		str[i++] = *s++;
	str[i] = '\0';
	return (str);
}
