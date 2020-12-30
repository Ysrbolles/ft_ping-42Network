/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 21:53:48 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/30 17:19:46 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	errorstr(char *errorstr)
{
	printf("%s\n", errorstr);
	exit(0);
}

void	create_socket(void)
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

void	get_statistic(void)
{
	struct timeval	start;
	struct timeval	end;
	double			loss;
	long double		time;
	long double		mdev;

	gettimeofday(&g_params->time.time_end, NULL);
	start = g_params->time.time_start;
	end = g_params->time.time_end;
	loss = (g_params->sended - g_params->reiceved)
	/ g_params->sended * 100.0;
	time = (end.tv_usec - start.tv_usec) / 1000000.0;
	time += (end.tv_sec - start.tv_sec);
	time *= 1000.0;
	g_params->time.avg /= g_params->sended;
	mdev = (g_params->time.sum_square / g_params->sended) -
		g_params->time.avg * g_params->time.avg;
	mdev = sqrt(mdev);
	printf("\n--- %s ping statistics ---\n", g_params->host);
	printf("%d packets trnasmitted, %d recived, ",
	g_params->sended, g_params->reiceved);
	printf("%.0f%% packet loss, time %.0Lfms\n", loss, time);
	printf("rtt min/avg/max/mdev = %.3Lf/%.3Lf/%.3Lf/%.3Lf ms\n",
	g_params->time.min, g_params->time.avg,
	g_params->time.max, mdev);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_params->signals.end = 1;
		get_statistic();
	}
	if (sig == SIGALRM)
		g_params->signals.send = 1;
}
