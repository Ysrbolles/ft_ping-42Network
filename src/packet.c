/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 20:28:18 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/20 16:42:49 by ybolles          ###   ########.fr       */
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
int send_packet()
{
	int i;

	i = 0;
	ft_bzero(&g_params.pkt, sizeof(g_params.pkt));
	g_params.pkt.hdr.type = ICMP_ECHO;
	g_params.pkt.hdr.un.echo.id = getpid();
	while (i++ < sizeof(g_params.pkt) - 1)
		g_params.pkt.msg[i] = i + '0';
	g_params.pkt.msg[i] = 0;
	g_params.pkt.hdr.un.echo.sequence = g_params.msg_count++;
	g_params.pkt.hdr.checksum = checksum(&g_params.pkt, sizeof(g_params.pkt));
	g_params.msg_count == 1 ? gettimeofday(&g_params.tfs, NULL) : 0;
	gettimeofday(&g_params.time_start, NULL);
	if (sendto(g_params.ClientSocket, &g_params.pkt, sizeof(g_params.pkt), 0, g_params.addr_info->ai_addr, g_params.addr_info->ai_addrlen) <= 0)
		g_params.flag = g_params.flag_v ? g_params.flag : 0;
}

long double calc(struct timeval start, struct timeval end)
{
	long double res;

	long int startII = end.tv_sec - start.tv_sec;
	printf("--------> start sec: %ld | --------> start usec: %ld\n", start.tv_sec, start.tv_usec);
	printf("-------->end sec: %ld | -------> end usec: %ld\n", end.tv_sec, end.tv_usec);
	long int endII = end.tv_usec - start.tv_usec;
	res = ((startII * 1000) + (endII / 1000));
	printf("------> res %ld\n", endII);
	return (res);
}

int get_packet()
{
	struct msghdr msg;
	struct iovec iov;
	int ret;
	char				buffer[4096];


	iov.iov_base = &buffer;
	iov.iov_len = sizeof(buffer);
	msg.msg_name = g_params.addr_info->ai_addr;
	msg.msg_namelen = g_params.addr_info->ai_addrlen;;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = 0;
	msg.msg_controllen = 0;
	ret = recvmsg(g_params.ClientSocket, &msg, MSG_DONTWAIT);
	if (!(ret <= 0 && g_params.msg_count > 1))
	{
		
		gettimeofday(&g_params.time_end, NULL);
		g_params.rtt = calc(g_params.time_start, g_params.time_end);
	}
	if (g_params.flag)
	{
		if (!g_params.flag_v)
		{
			printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.1Lf ms\n",
				   PACKET_PING_SIZE, g_params.addrstr, g_params.msg_count,
				   g_params.ttl, g_params.rtt);
			g_params.msg_countrecv++;
		}
		else if(g_params.flag_v)
		{
			printf("%d bytes from %s: type=%d icmp_seq=%d ttl=%d time=%.1Lf ms\n",
				   PACKET_PING_SIZE, g_params.addrstr, g_params.pkt.hdr.type,g_params.msg_count,
				   g_params.ttl, g_params.rtt);
		}
	}
	if (g_params.flag == 0)
	{
	}
	return 0;
}
