/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 20:28:18 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/11 18:17:12 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

unsigned short checksum(void *b, int len)
{
	unsigned short *buff = b;
	unsigned int sum =0;
	unsigned short result;
	
	while(len > 1)
	{
		sum += *(unsigned char*)buff;
		len -= 2;
	}
	if(len == 1)
		sum +=*(unsigned char*)buff;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return result;
}

int get_packet(t_params *params)
{
	t_ping_pkt pkt;
	pkt.hdr.type = ICMP_ECHO;
	pkt.hdr.un.echo.id = getpid();
	printf("--------------> CLientSocket (%d)\n----------------> IP (%s)\n--------------> PID (%d)\n"
			, params->ClientSocket,
			params->addrstr,
			pkt.hdr.un.echo.id);
	printf("-----------> PIDII (%d)\n" , getpid());
	return 0;
}
