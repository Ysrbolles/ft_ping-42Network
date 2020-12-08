/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 20:28:18 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/06 20:28:20 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

unsigned short checksum(unsigned short *buffer, int len)
{
	unsigned int sum;
	unsigned short result;

	sum = 0;
	while (len > 1)
		sum += *buffer++;
	if (len == 1)
		sum += *(unsigned char *)buffer;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return result;
}

void send_ping(int ClinetSocket, struct sockadrr *ping_addr, char *ping_dom, char *ping_ip, char *rev_host)
{
	int ttl_val = 64;
	int msg_count = 0;
	int i;
	int addr_len;
	int flag =1;
	int msgrecvcount = 0;
	struct msghdr *msg = {0};
	struct ping_pkt pckt;
	struct sockaddr r_addr;
	struct timeval time_start, time_end, tfs, tfe;
	struct timeval tv_out;
	tv_out.tv_sec = RECV-TIMEOUT;
	tv_out.tv_usec = 0;

	gettimeofday(tv_out, NULL);

	if(setsocketipt(ClinetSocket, SOL_IP, IP_TTL, &ttl_val, sizeof(ttl_val))!= 0)
	{
		printf("Setting socket Failed\n");
		return ;
	}
	else 
	{
		printf("Socket set to ttl..\n");
	}
	setsockopt(ping_sockfd, SOL_SOCKET, SO_RCVTIMEO,(const char*)&tv_out, sizeof tv_out);
	while(1)
	{
		flag = 1;
		ft_bzero(&pckt, sizeof(pckt));

		pckt.hdr.type = ICMP_ECHO;
		pckt.hdr.un.echo.id = getpid();
		i = 0;
		while(i < sizeof(pckt.msg)-1)
		{
			pckt.msg[i] = i+'0';
			i++;
		}
		pckt.msg[i] = 0;
		pckt.hdr.un.echo.sequence = msg_count++;
		pckt.hdr.checksum = checksum(&pckt, sizeof(pckt));
		if(sendto(ClientSocket, &pckt, sizeof(pckt), 0, (struct sockaddr*) ping_addr, sizeof(*ping_addr)) <= 0)
		{
			printf("Packet Sending Faild!\n");
			flag = 0;
		}
		addr_len = sizeof(r_addr);
		if(recvmsg(ClinetSocket, msg, MSG_DONTWAIT) < 0)
		{
			printf("Packet Recive Failed\n");
		}
		else
		{
			printf("DOne\n");
		}
	}

}	
