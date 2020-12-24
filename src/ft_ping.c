/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:38:07 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/22 22:15:42 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int get_addrinfo(char *host)
{
	struct addrinfo hints;
	struct addrinfo *servinfo;

	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;

	if (getaddrinfo(host, NULL, &hints, &servinfo) != 0)
		return 1;
	g_params.addr_info = servinfo;
	g_params.addrinfo = (struct sockaddr_in *)servinfo->ai_addr;
	return 0;
}

void init_params(void)
{
	ft_bzero(&g_params, sizeof(t_params));
	ft_bzero(&g_params.addr_info, sizeof(struct addrinfo));
	g_params.pingloop = 1;
	g_params.signalalarm = 1;
	g_params.pkt.ip = (struct iphdr)g_params.pkt.msg;
	g_params.pkt.hdr = g_params.pkt.ip;
	g_params.ttl = 63;
	g_params.msg_count = 0;
	g_params.msg_countrecv = 0;
	g_params.interval = 1;
	g_params.flag_v = 0;
	g_params.flag = 1;
}

void create_sock(void)
{
	int sockfd;
	int val;

	val = 1;
	g_params.tv_out.tv_sec = 0;
	g_params.tv_out.tv_usec = USEC_TIMEOUT;
	if (sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP) == -1)
		printf("Socket fd not received\n");
	/*if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &val, sizeof(int)) < 0)
	{
		printf("setsockopt Error\n");
		exit(0);
	}*/
	g_params.clientsocket = sockfd;
}

void call_ping(void)
{
	create_sock();
	printf("PING %s (%s) 56(84) bytes of data.\n", g_params.host, g_params.addrstr);
	while (g_params.pingloop)
	{
		if (g_params.signalalarm)
		{
			printf("/////////////////////////\n");
			send_packet();
			g_params.signalalarm = 0;
			printf("***********\n");
			alarm(g_params.interval);
			printf("-------\n");
			get_packet();
		}
	}
}
