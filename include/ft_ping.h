/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:04:29 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/06 10:06:30 by ybolles          ###   ########.fr       */
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
#include "ip_icmp.h"

#define PACKET_PING_SIZE 64
#define HEADERLEN ICMP

typedef struct s_flags
{
        int FLAG_V;
        int FLAG_H;
        char *HOST;
} t_flags;

struct ping_pkt 
{
  
   struct icmphdr hdr; 
   char msg[PACKET_PING_SIZE - sizeof(struct icmphdr)]; 
}g_pckt; 
#endif
