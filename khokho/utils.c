/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 10:59:50 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/10/09 14:49:44 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ping.h>

void			sec_sleep(int sec)
{
	struct timeval current;
	struct timeval next;

	gettimeofday(&current, NULL);
	next = current;
	next.tv_sec += sec;
	while ((current.tv_sec < next.tv_sec ||
			current.tv_usec < next.tv_usec) && (g_ping.pingloop))
		gettimeofday(&current, NULL);
}

unsigned short	checksum(void *b, int len)
{
	unsigned short	*buf;
	unsigned int	sum;

	buf = b;
	sum = 0;
	while (len > 1)
	{
		sum += *buf++;
		len -= 2;
	}
	if (len == 1)
		sum += *(unsigned char *)buf;
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	return ((unsigned short)~sum);
}

void			interupt_h(int sig)
{
	g_ping.pingloop = 0;
	(void)sig;
}

char			*dns_lookup(char *addr_host, struct sockaddr_in	*addr_con)
{
	struct addrinfo		hints;
	struct addrinfo		*res;
	struct sockaddr_in	*sa_in;
	char				*ip;

	memset(&(hints), 0, sizeof(hints));
	hints.ai_family = AF_INET;
	ip = malloc(INET_ADDRSTRLEN);
	if (getaddrinfo(addr_host, NULL, &hints, &(res)) < 0)
		exit_err("ping: unknown host\n");
	sa_in = (struct sockaddr_in *)res->ai_addr;
	inet_ntop(res->ai_family, &(sa_in->sin_addr), ip, INET_ADDRSTRLEN);
	(*addr_con) = *sa_in;
	(*addr_con).sin_port = htons(PORT);
	return (ip);
}

int				ping_help(int c, char **v)
{
	if (c == 1 || (c == 2 && v[1][0] == '-'
				&& v[1][1] == 'h' && v[1][2] == '\0'))
	{
		printf("usage: ./ft_ping [-vh] hostname\n");
		exit(0);
	}
	if (c == 2 && v[1][0] == '-'
			&& v[1][1] == 'v' && v[1][2] == '\0')
	{
		printf("usage: ./ft_ping [-vh] hostname\n");
		exit(0);
	}
	if ((c == 3 && v[1][0] == '-'
				&& v[1][1] == 'h' && v[1][2] == '\0'))
	{
		printf("usage: ./ft_ping [-vh] hostname\n");
		exit(0);
	}
	if (v[1][0] == '-' && v[1][1] == 'v' && v[1][2] == '\0')
		return (1);
	return (0);
}
