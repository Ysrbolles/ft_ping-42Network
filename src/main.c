/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 21:29:26 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/22 21:29:31 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_params g_params;

void parse_av(int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			if (av[i][1] == 'h')
			{
				printf("usage: ./ft_ping [-vh] hostname\n");
				exit(1);
			}
			else if (av[i][1] == 'v')
				g_params.flag_v = 1;
		}
		else
		{
			g_params.host = av[i];
			if (get_addrinfo(av[i]))
			{
				printf("Unknown name or services\n");
				exit(1);
			}
			inet_ntop(AF_INET, &((struct sockaddr_in *)(void *)g_params.addr_info->ai_addr)->sin_addr,
					g_params.addrstr, sizeof(g_params.addrstr));
			return;
		}
		i++;
	}
}

int main(int ac, char **av)
{

	if (getuid() != 0)
		printf("ft_ping: Operation not permitted\n");
	init_params();
	parse_av(ac, av);
	signal(SIGALRM, sighandler);
	signal(SIGINT, sighandler);
	call_ping();
	return (0);
}
