/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 21:53:48 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/25 14:41:39 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_params *g_params;

int	get_addrinfo(char *av)
{
	struct	addrinfo hints;
	struct	addrinfo *result;

	bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;

	if(getaddrinfo(av, NULL, &hints, &result) != 0)
		return 1;
	g_params->rec_in = (struct sockaddr_in*)result->ai_addr;
	return 0;
}
void    init_params(void)
{
	g_params = malloc(sizeof(t_params));
	bzero(g_params, sizeof(t_params));
	g_params->pckt.ip = (struct iphdr*)g_params->pckt.buf;
	g_params->pckt.hdr = (struct icmphdr*)(g_params->pckt.ip + 1);
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

void	sig_handler(int sig)
{
	if(sig == SIGINT)
	{
		printf("Ali \n");
		g_params->signals.send = 0;
	}
}

void	parsing(int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{	
			if (av[i][1] == 'h')
			{
				printf(USAGE"\n");
				exit(0);
			}
			else if (av[i][1] == 'v')
				g_params->flags |= FLAG_V;
			
		}
		else
		{
			if(get_addrinfo(av[i]))
			{
				printf("Unknow name or services\n");
				exit(0);
			}
			g_params->host = av[i];
			inet_ntop(AF_INET, (void*)&g_params->rec_in->sin_addr, g_params->addrstr, INET6_ADDRSTRLEN);
			printf("------> %s \n", g_params->addrstr);
			return ;
		}
		i++;
	}
}
void	create_socket()
{
	int sockfd;

	if((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
	{
		printf("Socket file descriptor not received!");
		exit(0);
	}
}
void	start_ping()
{
	create_socket();
}

int main(int ac, char **av)
{
	if (getuid() != 0)
	{
		printf("ft_ping: Operation not permitted\n");
		exit(0);
	}
	if (ac < 2)
	{
		printf("Usage: ft_ping [-v verbose] [Options] destination\n");
		exit(0);
	}
	init_params();
	parsing(ac, av);
	signal(SIGALRM, sig_handler);
	signal(SIGINT, sig_handler);
	start_ping();
}
