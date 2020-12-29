/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 21:53:48 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/29 10:59:01 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void create_socket()
{
	int sockfd;
	int opt_val;

	opt_val = 1;
	if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
	{
		printf("Socket file descriptor not received!\n");
		exit(0);
	}
	if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &opt_val, sizeof(int)) < 0)
	{
		printf("setsockopt Error\n");
		exit(0);
	}
	g_params->sockfd = sockfd;
}

void sig_handler(int sig)
{
	double	loss;
	long double time;

	if (sig == SIGINT)
	{
		g_params->signals.end = 1;
		gettimeofday(&g_params->time.time_end, NULL);
		loss = (g_params->sended - g_params->reiceved) / g_params->sended * 100.0;
		time = (g_params->time.time_end.tv_usec - g_params->time.time_start.tv_usec) / 1000.0;
		g_params->time.sum_square = (g_params->time.sum_square / g_params->sended) - g_params->time.avg * g_params->time.avg;
		printf("\n--- %s ping statistics ---\n", g_params->host);
		printf("%d packets trnasmitted, %d recived, %.0f%% packet loss, time %Lfms\n",
			       	g_params->sended, g_params->reiceved, loss, time);
		printf("rtt min/avg/max/mdev = %.3Lf/%.3Lf/%.3Lf/%.3Lf ms\n", g_params->time.min,
				(g_params->time.avg / g_params->sended), g_params->time.max, g_params->time.sum_square);
	}
	if(sig == SIGALRM)
		g_params->signals.send = 1;
}
