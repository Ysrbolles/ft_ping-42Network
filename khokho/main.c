/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 13:26:02 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/10/10 08:40:20 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ping.h>

t_main		*init_ping(void)
{
	t_main *p;

	p = (t_main *)malloc(sizeof(t_main));
	p->rtt_msec = 0;
	p->total_msec = 0;
	p->tv_out.tv_sec = RECV_TIMEOUT;
	p->tv_out.tv_usec = 0;
	p->ttl_val = 63;
	p->msg_count = 0;
	p->msg_received_count = 0;
	p->flag = 1;
	p->addr_len = sizeof(p->r_addr);
	return (p);
}

t_ping		create_msg(int *msg_count)
{
	t_ping	pckt;
	int		i;

	i = -1;
	bzero(&pckt, sizeof(pckt));
	while (++i < (int)sizeof(pckt.msg) - 1)
		pckt.msg[i] = i + '0';
	pckt.msg[i] = 0;
	pckt.hdr.type = ICMP_ECHO;
	pckt.hdr.un.echo.id = getpid();
	pckt.hdr.un.echo.sequence = (*msg_count)++;
	pckt.hdr.checksum = checksum(&pckt, sizeof(pckt));
	return (pckt);
}

void		ping_print(t_main *p, int type, char *ping_dom)
{
	double time_elapsed;
	double pkt_loss;

	if (type == 1)
	{
		printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.1Lf ms\n",
				PING_PKT_SIZE, p->ip_addr, p->msg_count,
				p->ttl_val, p->rtt_msec);
		p->msg_received_count++;
	}
	else
	{
		gettimeofday(&p->tfe, NULL);
		time_elapsed = (double)((p->tfe.tv_usec - p->tfs.tv_usec) / 1000.0);
		p->total_msec = (((p->tfe.tv_sec - p->tfs.tv_sec)) *
				1000 + time_elapsed) - (p->msg_count * 130);
		pkt_loss = (double)(((p->msg_count -
						p->msg_received_count) / p->msg_count) * 100);
		printf("\n--- %s ping statistics ---\n", ping_dom);
		printf("%d packets transmitted, %d packets received, ",
				p->msg_count, p->msg_received_count);
		printf("%d%% packet loss, time %d ms\n", (int)pkt_loss,
				(int)p->total_msec);
	}
}

void		ft_ping(t_main *p, struct sockaddr_in *ping_addr, char *domain)
{
	setsockopt(p->sockfd, SOL_IP, IP_TTL, &p->ttl_val, sizeof(p->ttl_val));
	setsockopt(p->sockfd, SOL_SOCKET, SO_RCVTIMEO,
			(const char *)&p->tv_out, sizeof(p->tv_out));
	while (g_ping.pingloop)
	{
		ft_ping_msg(p);
		if (sendto(p->sockfd, &p->pckt, sizeof(p->pckt), 0,
					(struct sockaddr *)ping_addr, sizeof(*ping_addr)) <= 0)
			p->flag = (p->v) ? p->flag : 0;
		if (!(recvfrom(p->sockfd, &p->pckt, sizeof(p->pckt), 0,
						(struct sockaddr*)&p->r_addr, (t_len*)&p->addr_len) <= 0
					&& p->msg_count > 1))
		{
			gettimeofday(&p->time_end, NULL);
			p->rtt_msec = ((double)(p->time_end.tv_usec -
						p->time_start.tv_usec)) / 1000;
			if (p->flag && (p->pckt.hdr.type == 69 && p->pckt.hdr.code == 0))
				ping_print(p, 1, domain);
			else
				error_report(p);
		}
		sec_sleep(1);
	}
	ping_print(p, 0, domain);
}

int			main(int c, char **v)
{
	struct sockaddr_in	addr_con;
	t_main				*p;

	signal(SIGINT, interupt_h);
	if (c >= 2 && c < 4)
	{
		p = init_ping();
		p->v = ping_help(c, v);
		g_ping.pingloop = 1;
		p->ip_addr = dns_lookup((c == 2) ? v[1] : v[2], &addr_con);
		p->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
		if (p->sockfd && p->ip_addr)
		{
			printf("PING %s (%s) 56(84) bytes of data.\n",
					(c == 2) ? v[1] : v[2], p->ip_addr);
			ft_ping(p, &addr_con, v[1]);
		}
	}
	else
		ping_help(c, v);
	return (0);
}
