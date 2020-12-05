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

int parse_flag(char s)
{
    t_flags flags;
    if (!s)
        return 0;

    if (s == 'v')
    {
        flags.FLAG_V = 1;
        return 1;
    }
    else if (s == 'h')
    {
        flags.FLAG_V = 1;
        return 1;
    }
    return 0;
}

int main(int ac, char **av)
{
    if (ac > 2 && *av)
    {
        int i;
        int state;
        char **tab;

        i = 0;
        if (*av && av[1][0] == '-')
        {
            state = parse_flag(av[1][1]);
            printf("%d\n", state);
        }
    }
    else
    {
        printf("khriwa\n");
    }
    return 0;
}