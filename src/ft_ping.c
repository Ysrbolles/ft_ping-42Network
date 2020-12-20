/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:38:07 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/20 12:52:50 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void init_params(void)
{

	g_params.rtt = 0;
	g_params.total = 0;
	g_params.pingloop = 1;
	g_params.tv_out.tv_sec = RECV_TIMEOUT;
	g_params.tv_out.tv_usec = 0;
	g_params.ttl = 63;
	g_params.ttlptr = NULL;
	g_params.recv_ttl = 0;
	g_params.msg_count = 0;
	g_params.msg_countrecv = 0;
	g_params.flag = 1;
}

struct addrinfo *copy(struct addrinfo *value)
{
	struct addrinfo *on;

	on = malloc(sizeof(struct addrinfo *));
	on->ai_family = value->ai_family;
	on->ai_socktype = value->ai_socktype;
	on->ai_protocol = value->ai_protocol;
	on->ai_addrlen = value->ai_addrlen;
	on->ai_addr = malloc(sizeof(struct sockaddr *));
	on->ai_addr = value->ai_addr;
	on->ai_canonname = value->ai_canonname;
	return (on);
}

int socket_while(struct addrinfo *rp)
{
	int sock = 0;
	int i;

	i = 0;
	while (rp != NULL)
	{
		sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sock == -1)
			continue;
		if (sock != -1)
		{
			g_params.addr_info = copy(rp);
			return (sock);
		}
		rp = rp->ai_next;
		i++;
	}
	return (sock);
}

int create_sock()
{
	int sockfd;
	struct addrinfo hints;
	struct addrinfo *servinfo;
	int sock;
	int rv;

	ft_memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	hints.ai_flags = 0;
	if ((rv = getaddrinfo(g_params.Host, NULL, &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(1);
	}
	sockfd = socket_while(servinfo);
	if(setsockopt(sockfd, IPPROTO_IP, IP_TTL, &g_params.ttl, sizeof(g_params.ttl) != 0))
		printf("\n-- khnouna ---\n");
	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,
			(const char *)&g_params.tv_out, sizeof(g_params.tv_out));
	return (sockfd);
}
void ft_sleep(int sec)
{
	struct timeval current;
	struct timeval next;

	gettimeofday(&current, NULL);
	next = current;
	next.tv_sec += sec;
	while ((current.tv_sec < next.tv_sec ||
			current.tv_usec < next.tv_usec) &&
		   (g_params.pingloop))
		gettimeofday(&current, NULL);
}
