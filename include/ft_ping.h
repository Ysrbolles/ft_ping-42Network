/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:04:29 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/11 18:26:43 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
#define FT_PING_H
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "libft.h"
#include <netinet/ip_icmp.h>
#include <signal.h>
#include <sys/time.h>

#define PACKET_PING_SIZE 64
#define HEADERLEN ICMP



typedef struct s_flags
{
	int FLAG_V;
	int FLAG_H;
	char *HOST;
	struct addrinfo info;
} t_flags;

typedef struct s_params
{
	int pingloop;
	struct addrinfo *addr_info;
	int ClientSocket;
	struct timeval start_time;
	char  addrstr[INET_ADDRSTRLEN];
	char *Host;

} t_params;

extern t_params *params;

typedef struct s_ping_pkt
{
	struct icmphdr hdr;
	char msg[PACKET_PING_SIZE - sizeof(struct icmphdr)];
} t_ping_pkt;

unsigned short checksum(void *b, int len);
int	get_packet();
int	send_packet();
void	start_signal();
void 	intHandler(int dummy);
#endif
