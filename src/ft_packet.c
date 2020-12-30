/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_packet.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 21:53:48 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/30 09:44:19 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	send_packet(void)
{
	bzero((void *)g_params->pckt.buf, PACKET_PING_SIZE);
	g_params->pckt.ip->version = 4;
	g_params->pckt.ip->ihl = sizeof(*g_params->pckt.ip) >> 2;
	g_params->pckt.ip->ttl = g_params->ttl;
	g_params->pckt.ip->protocol = IPPROTO_ICMP;
	inet_pton(AF_INET, g_params->addrstr, &g_params->pckt.ip->daddr);
	g_params->daddr = g_params->pckt.ip->daddr;
	g_params->pckt.hdr->type = ICMP_ECHO;
	g_params->pckt.hdr->code = 0;
	g_params->pckt.hdr->un.echo.id = g_params->pid;
	g_params->pckt.hdr->un.echo.sequence = g_params->seq++;
	g_params->pckt.hdr->checksum = checksum((unsigned short*)g_params->pckt.hdr,
	sizeof(struct icmphdr));
	if (sendto(g_params->sockfd, (void *)&g_params->pckt, PACKET_PING_SIZE, 0,
	(void *)g_params->rec_in,
	sizeof(struct sockaddr_in)) < 0)
	{
		printf("sendto Error\n");
		exit(0);
	}
	if (gettimeofday(&g_params->time.s, NULL) < 0)
		errorstr("gettimeofday Error\n");
	g_params->sended > 1 ? gettimeofday(&g_params->time.time_start, NULL) : 0;
	g_params->sended++;
	g_params->signals.send = 0;
}

void	calc_rtt(void)
{
	long double rtt;

	if (gettimeofday(&g_params->time.r, NULL) < 0)
		errorstr("gettimeofday Error!");
	g_params->reiceved++;
	rtt = (g_params->time.r.tv_usec - g_params->time.s.tv_usec) / 1000000.0;
	rtt += (g_params->time.r.tv_sec - g_params->time.s.tv_sec);
	rtt *= 1000.0;
	g_params->time.rtt = rtt;
	if (rtt > g_params->time.max)
		g_params->time.max = rtt;
	if (rtt < g_params->time.min || g_params->time.min == 0.0)
		g_params->time.min = rtt;
	g_params->time.avg += rtt;
	g_params->time.sum_square += rtt * rtt;
}

void	init_header(void)
{
	t_res	*res;

	res = &g_params->response;
	bzero((void *)g_params->pckt.buf, PACKET_PING_SIZE);
	bzero(res, sizeof(t_res));
	res->iov->iov_base = (void *)g_params->pckt.buf;
	res->iov->iov_len = sizeof(g_params->pckt.buf);
	res->msg.msg_iov = res->iov;
	res->msg.msg_iovlen = 1;
	res->msg.msg_name = NULL;
	res->msg.msg_namelen = 0;
	res->msg.msg_flags = MSG_DONTWAIT;
}

void	printf_v(void)
{
	char		str[50];

	printf("%d bytes from %s: type=%d code=%d\n",
	g_params->bytes - (int)sizeof(struct iphdr),
	inet_ntop(AF_INET, (void*)&g_params->pckt.ip->saddr, str, 100),
	g_params->pckt.hdr->type, g_params->pckt.hdr->code);
}

void	get_packet(void)
{
	int			ret;

	init_header();
	while (!g_params->signals.end)
	{
		ret = recvmsg(g_params->sockfd, &g_params->response.msg, MSG_DONTWAIT);
		if (ret > 0)
		{
			g_params->bytes = ret;
			if (g_params->pckt.hdr->un.echo.id == g_params->pid)
			{
				calc_rtt();
				printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.2Lf ms\n",
				g_params->bytes - (int)sizeof(struct iphdr), g_params->addrstr,
				g_params->pckt.hdr->un.echo.sequence, g_params->pckt.ip->ttl,
				g_params->time.rtt);
			}
			else if (g_params->flags & FLAG_V)
				printf_v();
			return ;
		}
	}
}
