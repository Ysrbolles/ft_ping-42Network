/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 21:53:48 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/31 15:19:12 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_params *g_params;

void	init_params(void)
{
	g_params = malloc(sizeof(t_params));
	ft_bzero(g_params, sizeof(t_params));
	g_params->pckt.ip = (struct iphdr *)g_params->pckt.buf;
	g_params->pckt.hdr = (struct icmphdr *)(g_params->pckt.ip + 1);
	g_params->pid = getpid();
	g_params->seq = 1;
	g_params->time.min = 0.0;
	g_params->time.max = 0.0;
	g_params->time.sum_square = 0;
	g_params->ttl = TTL;
	g_params->count = -1;
	g_params->interval = 1;
	g_params->signals.send = 1;
	g_params->signals.end = 0;
}

void	parsing(int ac, char **av)
{
	int i;

	i = 0;
	while (i++ < ac)
	{
		if (av[i][0] == '-')
		{
			if (av[i][1] == 'h')
				errorstr(USAGE);
			else if (av[i][1] == 'v')
				g_params->flags |= FLAG_V;
			else
				errorstr(USAGE);
		}
		else
		{
			g_params->host = av[i];
			if (get_addrinfo(av[i]))
			{
				printf("ft_ping: %s : ", g_params->host);
				errorstr("Name or service not known");
			}
			inet_ntop(AF_INET, (void *)&g_params->rec_in->sin_addr,
			g_params->addrstr, INET6_ADDRSTRLEN);
			return ;
		}
	}
}

int		main(int ac, char **av)
{
	if (getuid() != 0)
		errorstr("ft_ping: Operation not permitted");
	if (ac < 2)
		errorstr(USAGE);
	init_params();
	parsing(ac, av);
	signal(SIGALRM, sig_handler);
	signal(SIGINT, sig_handler);
	start_ping();
	return (0);
}
