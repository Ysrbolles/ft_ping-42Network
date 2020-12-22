/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 20:28:18 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/22 22:26:32 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

unsigned short checksum(void *b, int len)
{
	unsigned short *buff = b;
	unsigned int sum = 0;
	unsigned short result;

	while (len > 1)
	{
		sum += *(unsigned char *)buff;
		len -= 2;
	}
	if (len == 1)
		sum += *(unsigned char *)buff;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return result;
}

void send_packet(void)
{
	ft_bzero((void *)g_params.pkt.msg, PACKET_PING_SIZE);
	g_params.pkt.ip.version = 4;
	g_params.pkt.ip.ihl = sizeof(g_params.pkt.ip) >> 2;
	g_params.pkt.ip.ttl = g_params.ttl;
	inet_pton(AF_INET, g_params.addrstr, &g_params.pkt.ip.daddr);
	g_params.daddr = g_params.pkt.ip.daddr;
	g_params.pkt.hdr.type = ICMP_ECHO;
	g_params.pkt.hdr.code = 0;
	g_params.pkt.hdr.un.echo.id = getpid();
	g_params.pkt.hdr.un.echo.sequence = g_params.msg_count++;
	g_params.pkt.hdr.checksum = checksum((unsigned short *)&g_params.pkt.hdr, sizeof(struct icmphdr));
	if (sendto(g_params.clientsocket, &g_params.pkt, PACKET_PING_SIZE, 0,
			   g_params.addrinfo, sizeof(struct sockaddr_in)) < 0)
	{
		printf("sendto socket Error\n");
		exit(0);
	}
	if (gettimeofday(&g_params.time_start, NULL) < 0)
	{
		printf("gettimeofday Error\n");
		exit(0);
	}
}

void get_packet(void)
{
	t_res result;
	int ret;

	result = g_params.res;
	ft_bzero(&g_params.pkt.msg, PACKET_PING_SIZE);
	ft_bzero(&result, sizeof(t_res));
	result.iov->iov_base = g_params.pkt.msg;
	result.iov->iov_len = sizeof(g_params.pkt.msg);
	result.msg.msg_iov = result.iov;
	result.msg.msg_iovlen = 1;
	result.msg.msg_name = NULL;
	result.msg.msg_namelen = 0;

	while (!g_params.signalalarm)
	{
		ret = recvmsg(g_params.clientsocket, &g_params.res.msg, MSG_DONTWAIT);
		if (ret > 0)
		{
			if (g_params.pkt.hdr.un.echo.id == getpid())
			{
				if (gettimeofday(&g_params.time_end, NULL) < 0)
				{
					printf("gettimeofday Error\n");
					exit(0);
				}
				g_params.msg_countrecv++;
				g_params.rtt = (g_params.time_end.tv_usec - g_params.time_start.tv_usec) / 1000000.0;
				g_params.rtt += (g_params.time_end.tv_sec - g_params.time_start.tv_sec);
				g_params.rtt *= 1000.0;
				printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.Lf ms\n", 64, g_params.addrstr,
					   g_params.msg_count, g_params.ttl, g_params.rtt);
			}
			else if (g_params.flag && g_params.flag_v)
				printf("%d bytes from %s: type = %d code = %d\n", 64, g_params.addrstr, g_params.pkt.hdr.type, g_params.pkt.hdr.code);
		}
	}
}
