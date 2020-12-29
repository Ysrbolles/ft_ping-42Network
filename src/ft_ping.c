/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 21:53:48 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/29 16:09:44 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

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

int				get_addrinfo(char *av)
{
	struct addrinfo hints;
	struct addrinfo *result;

	bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	if (getaddrinfo(av, NULL, &hints, &result) != 0)
		return (1);
	g_params->rec_in = (struct sockaddr_in *)result->ai_addr;
	return (0);
}

void			start_ping(void)
{
	create_socket();
	printf("PING %s (%s) %d(%d) bytes of data.\n", g_params->host,
	g_params->addrstr, 56, 84);
	while (!g_params->signals.end)
	{
		if (g_params->signals.send)
		{
			send_packet();
			alarm(1);
			get_packet();
		}
	}
}
