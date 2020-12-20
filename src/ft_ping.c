/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:38:07 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/19 13:47:09 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void init_params(void)
{

	params.rtt = 0;
	params.total = 0;
	params.tv_out.tv_sec = RECV_TIMEOUT;
	params.tv_out.tv_usec = 0;
	params.ttl = 63;
	params.msg_count = 0;
	params.msg_countrecv = 0;
	params.flag = 1;
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
			params.addr_info = copy(rp);
			return (sock);
		}
		rp = rp->ai_next;
		i++;
	}
	return (sock);
}

int cerate_sock()
{
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int sock;
	int rv;

	params.pingloop = 1;
	ft_memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	hints.ai_flags = 0;
	if ((rv = getaddrinfo(params.Host, NULL, &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(1);
	}
	sockfd = socket_while(servinfo);
	setsockopt(sockfd, IPPROTO_IP, IP_TTL, &params.ttl, sizeof(params.ttl));
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
		   (params.pingloop))
		gettimeofday(&current, NULL);
}

int main(int ac, char **av)
{
	struct timeval start;
	struct end;
	if (getuid() != 0)
		printf("ft_ping: Operation not permitted\n");
	if (ac != 2)
	{
		printf("Usage ERROR \n");
		exit(1);
	}
	else
	{

		init_params();
		params.Host = av[1];
		if ((params.ClientSocket = cerate_sock()) == -1)
			printf("Socket Failed\n");
		inet_ntop(params.addr_info->ai_family, &((struct sockaddr_in *)(void *)params.addr_info->ai_addr)->sin_addr, params.addrstr, sizeof(params.addrstr));
		printf("PING %s (%s) %zu(%zu) bytes of data.\n",
			   av[1], params.addrstr,
			   56, 58);
		start_signal();

		while (params.pingloop)
		{
			get_packet();
			ft_sleep(1);
		}
	}

	return (0);
}
