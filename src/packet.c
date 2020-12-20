/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 20:28:18 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/20 12:59:17 by ybolles          ###   ########.fr       */
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

	long double startII = end.tv_sec - start.tv_sec;
	long double endII = end.tv_usec - start.tv_usec;
	res = (long double)((startII * 1000.) + (endII / 1000.));
	printf("------> res %Lf\n", res);
	return (res);
}

int get_packet()
{
	struct msghdr msg;
	struct iovec iov;
	int ret;
	char buf[CMSG_SPACE(sizeof(received_ttl))];

	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_name = g_params.addr_info->ai_addr;
	msg.msg_namelen = g_params.addr_info->ai_addrlen;
	msg.msg_control = buf;			  // Assign buffer space for control header + header data/value
	msg.msg_controllen = sizeof(buf); //just initializing it
	ret = recvmsg(g_params.ClientSocket, &msg, MSG_DONTWAIT);
	if (!(ret <= 0))
	{
		struct cmsghdr *cmsg;

		cmsg = CMSG_FIRSTHDR(&msg);
		while (cmsg != NULL)
		{
			if ((cmsg->cmsg_level == IPPROTO_ICMP) && (cmsg->cmsg_type == IP_TTL) &&
				(cmsg->cmsg_len))
			{
				g_params.ttlptr = (int *)CMSG_DATA(cmsg);
				g_params.recv_ttl = *g_params.ttlptr;
				printf("received_ttl = %i and %d \n", g_params.ttlptr, g_params.recv_tt);
				break;
			}
			cmsg = CMSG_NXTHDR(&msg, cmsg)
		}
		gettimeofday(&g_params.time_end, NULL);
		g_params.rtt = calc(g_params.time_start, g_params.time_end);
	}
	if (g_params.flag)
	{
		if ((g_params.pkt.hdr.type == 69 && g_params.pkt.hdr.code == 0))
		{
			printf("%d bytes from %s: ismp_seq=%d ttl=%d time=%.1Lf ms\n",
				   PACKET_PING_SIZE, g_params.addrstr, g_params.msg_count,
				   g_params.ttl, g_params.rtt);
			g_params.msg_countrecv++;
		}
		else
		{
			printf(" bo3o\n");
		}
	}
	if (g_params.flag == 0)
	{
	}
	return 0;
}