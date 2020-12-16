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
	unsigned int sum = 0;
	unsigned short result;

	while (len > 1)
	{
		sum += *(unsigned char *)buff;
		len -= 2;
	}
	if (len == 1)
		sum += *(unsigned char *)buff;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return result;
}
int send_packet()
{
	t_ping_pkt pkt;
	int sending;
	int i;

	bzero(&pkt, sizeof(pkt));
	i = -1;
	while(++i < (int)sizeof(pkt.msg) - 1)
		pkt.msg[i] = i + '0';
	pkt.msg[i] = 0;
	pkt.hdr.type = ICMP_ECHO;
	pkt.hdr.un.echo.id = getpid();
	pkt.hdr.un.echo.sequence = params.msg_count++;
	pkt.hdr.checksum = 0;
	pkt.hdr.checksum = checksum((unsigned short *)&pkt, sizeof(pkt));
	gettimeofday(&params.time_start, NULL);
	params.msg_count == 1 ? gettimeofday(&params.tfs, NULL): 0;
	if (sending = sendto(params.ClientSocket, &pkt, sizeof(pkt), 0, params.addr_info->ai_addr, params.addr_info->ai_addrlen) <= 0)
		params.flag = params.flag_v ? params.flag : 0;
}
int get_packet()
{
	struct msghdr msg;
	struct iovec iov[1];
	int ret;
	char buffer[80];

	iov[0].iov_base = buffer;
	iov[0].iov_len = sizeof(buffer);
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;
	msg.msg_name = params.addr_info->ai_addr;
	msg.msg_namelen = params.addr_info->ai_addrlen;
	if(!(ret = recvmsg(params.ClientSocket, &msg, MSG_DONTWAIT) < 0 && params.msg_count  >1)){
		gettimeofday(&params.time_end, NULL);
		params.rtt = ((double)(params.time_end.tv_usec - params.time_start.tv_usec)) / 1000;
	}
	if(params.flag && (params.pkt.hdr.type == 69 && params.pkt.hdr.code == 0))
	{
		printf("%d bytes from %s: ismp_seq=%d ttl=%d time%.1Lf ms\n",
			PACKET_PING_SIZE, params.addrstr, params.msg_count,
			params.ttl, params.rtt);
		params.msg_countrecv++;
	}
	printf("------------> Ret = %d\n", ret);
	if (ret < 0)
		printf("------------> Makhdmatch 3awtani hahahahah\n");

	return 0;
}
