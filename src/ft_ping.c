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

int parse_flag(char *s)
{
    t_flags flags;
    if (!*s)
        return 0;

    if (*s == 'v')
    {
        flags.FLAG_V = 1;
        return 1;
    }
    else if (*s == 'h')
    {
        flags.FLAG_V = 1;
        return 1;
    }
    return 0;
}


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
                int state = parse_flag(&tab[i][1]);
                printf("%d\n", state);
            }
        }
    }
    else
    {
        printf("khriwa\n");
    }
    return 0;
}