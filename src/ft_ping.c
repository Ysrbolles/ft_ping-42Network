/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:38:07 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/03 16:38:09 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int main(int ac, char **av)
{
    if (ac > 2 && av)
    {
        int i;
        char **tab;

        i = 0;
        tab = malloc(sizeof(char *) * ac - 1);
        while (++i < ac)
        {
            tab[i] = malloc(sizeof(char) * (strlen(av[i]) + 1));
            tab[i] = av[i];
            printf("%s\n", tab[i]);
        }
        i = 0;
        while (++i < ac - 1)
        {
            if (tab[i][0] == '-')
            {
                    printf("li hdhghfgjgjgvjfgaaaaak\n");
                if (tab[i][1] == 'v')
                {
                    printf("li hdaaaaak\n");
                }
            }
        }
    }
    else
    {
        printf("khriwa");
    }
    return 0;
}