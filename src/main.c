/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 21:53:48 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/25 17:37:33 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_params *g_params;

unsigned short	checksum(unsigned short *data, int len)
{
	unsigned long	checksum;

	checksum = 0;
	while (len > 1)
	{
		checksum = checksum + *data++;
		len = len - sizeof(unsigned short);
	}
	if (len)
		checksum = checksum + *(unsigned char*)data;
	checksum = (checksum >> 16) + (checksum & 0xffff);
	checksum = checksum + (checksum >> 16);
	return (unsigned short)(~checksum);
}

int get_addrinfo(char *av)
{
	struct addrinfo hints;
	struct addrinfo *result;

	bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;

	if (getaddrinfo(av, NULL, &hints, &result) != 0)
		return 1;
	g_params->rec_in = (struct sockaddr_in *)result->ai_addr;
	return 0;
}
void init_params(void)
{
	g_params = malloc(sizeof(t_params));
	bzero(g_params, sizeof(t_params));
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

void sig_handler(int sig)
{
	if (sig == SIGINT)
		g_params->signals.end = 1;
	if(sig == SIGALRM)
		g_params->signals.send = 1;
}

void parsing(int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			if (av[i][1] == 'h')
			{
				printf(USAGE "\n");
				exit(0);
			}
			else if (av[i][1] == 'v')
				g_params->flags |= FLAG_V;
		}
		else
		{
			if (get_addrinfo(av[i]))
			{
				printf("Unknow name or services\n");
				exit(0);
			}
			g_params->host = av[i];
			inet_ntop(AF_INET, (void *)&g_params->rec_in->sin_addr, g_params->addrstr, INET6_ADDRSTRLEN);
			printf("------> %s \n", g_params->addrstr);
			return;
		}
		i++;
	}
}
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
	printf("-----> sockfd %d\n", g_params->sockfd);
}

void	send_packet()
{
	bzero((void*)g_params->pckt.buf, PACKET_PING_SIZE);
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
	g_params->pckt.hdr->checksum = checksum((unsigned short*)g_params->pckt.hdr, sizeof(struct icmphdr));
	if(sendto(g_params->sockfd, (void*)&g_params->pckt, PACKET_PING_SIZE,0, (void*)g_params->rec_in, sizeof(struct sockaddr_in)) < 0)
	{
		printf("sendto Error\n");
		exit(0);
	}
	if(gettimeofday(&g_params->time.s, NULL) < 0)
	{
		printf("gettimeofday Error\n");
		exit(0);
	}
	g_params->sended++;
	g_params->signals.send = 0;

}

void	get_packet()
{
	int	ret;
	t_response *res;
	long double rtt;

	res = &g_params->response;
	bzero((void*)g_params->pckt.buf, PACKET_PING_SIZE);
	bzero(res, sizeof(t_response));
	res->iov->iov_base = (void*)g_params->pckt.buf;
	res->iov->iov_len = sizeof(g_params->pckt.buf);
	res->msg.msg_iov = res->iov;
	res->msg.msg_iovlen = 1;
	res->msg.msg_name = NULL;
	res->msg.msg_namelen = 0;
	res->msg.msg_flags = MSG_DONTWAIT;

	while(!g_params->signals.end)
	{
		ret = recvmsg(g_params->sockfd, &g_params->response.msg, MSG_DONTWAIT);
		if(ret > 0)
		{
			g_params->bytes = ret;
			if(g_params->pckt.hdr->un.echo.id == g_params->pid)
			{
				if(gettimeofday(&g_params->time.r, NULL) < 0)
				{
					printf("gettimeofday ERROR\n");
					exit(0);
				}
				g_params->reiceved++;
				rtt = (g_params->time.r.tv_usec - g_params->time.s.tv_usec) / 1000000.0;
				rtt += (g_params->time.r.tv_sec - g_params->time.s.tv_sec);
				rtt *= 1000.0;
				g_params->time.rtt = rtt;
				if(rtt > g_params->time.max)
					g_params->time.max = rtt;
				if(rtt < g_params->time.min || g_params->time.min == 0.0)
					g_params->time.min = rtt;
				g_params->time.avg += rtt;
				g_params->time.sum_square += rtt*rtt;
			       printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.2Lf ms\n", g_params->bytes - (int)sizeof(struct iphdr)
				    , g_params->addrstr, g_params->pckt.hdr->un.echo.sequence, g_params->pckt.ip->ttl, rtt);	
			}
			return ;
		}
	}


}

void start_ping()
{
	create_socket();
	printf("PING %s (%s) %d(%d) bytes of data.\n", g_params->host, g_params->addrstr, 56,84);
	while(!g_params->signals.end)
	{
		if(g_params->signals.send)
		{
			send_packet();
			alarm(1);
			get_packet();
		}
	}
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
