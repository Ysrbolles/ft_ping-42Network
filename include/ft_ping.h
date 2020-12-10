/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:04:29 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/10 14:02:42 by ybolles          ###   ########.fr       */
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
        struct addrinfo *addr_info;
        int ClinetSocket;
} t_params;

typedef struct ping_pkt
{
        struct icmphdr hdr;
        char msg[PACKET_PING_SIZE - sizeof(struct icmphdr)];
} g_pckt;

unsigned short checksum(unsigned short *buffer, int len);

#endif
