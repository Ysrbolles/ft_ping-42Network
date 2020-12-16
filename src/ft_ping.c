/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:38:07 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/11 18:31:15 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"


struct addrinfo *copy(struct addrinfo *value)
{
	struct addrinfo *on;

	on = malloc(sizeof(struct addrinfo *));

	on->ai_family = value->ai_family;
	on->ai_socktype = value->ai_socktype;
	on->ai_protocol = value->ai_protocol;
	on->ai_addrlen = value->ai_addrlen;
	on->ai_addr = value->ai_addr;
	on->ai_canonname = value->ai_canonname;
	return (on);
}

int socket_while(struct addrinfo *rp)
{
	int sock = 0;
	int i = 0;
	while (rp != NULL)
	{
		sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sock == -1)
		{
			continue;
		}
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

/*
 **
 */

int cerate_sock(char *av)
{
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int sock;
	int rv;

	params.pingloop = 1;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;		  // Set IP family to IPv4
	hints.ai_socktype = SOCK_RAW;	  // Set socket type to RAW
	hints.ai_protocol = IPPROTO_ICMP; // set Protocol to ICMP protocol
	hints.ai_flags = 0;
	printf("Host Name ------> %s\n", av);
	if ((rv = getaddrinfo(av, NULL, &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(1);
	}
	sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	sockfd = socket_while(servinfo);
	return (sockfd);
}
void			ft_sleep(int sec)
{
	struct timeval current;
	struct timeval next;

	gettimeofday(&current, NULL);
	next = current;
	next.tv_sec += sec;
	while ((current.tv_sec < next.tv_sec ||
				current.tv_usec < next.tv_usec) && (params.pingloop))
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

		params.Host = malloc(sizeof(av[1]));
		params.Host = av[1];
		if ((params.ClientSocket = cerate_sock(av[1])) == -1)
			printf("Socket Failed\n");
		setsockopt(params.ClientSocket, SOL_IP, IP_TTL, &params.ttl, sizeof(params.ttl));
		inet_ntop(params.addr_info->ai_family, &((struct sockaddr_in *)(void *)params.addr_info->ai_addr)->sin_addr, params.addrstr, sizeof(params.addrstr));
		printf("PING %s (%s) %zu(%zu) bytes of data.\n",
				av[1], params.addrstr,
				56, sizeof(t_ping_pkt) + 20);
		gettimeofday(&params.start_time, NULL);
		start_signal();
		while (params.pingloop)
		{
			get_packet();
			ft_sleep(2);

		}
	}

	return (0);
}
