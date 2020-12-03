/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:04:29 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/03 19:04:32 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
#define FT_PING_H
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h> 
# include <sys/socket.h>
# include <netdb.h>
# include <stdlib.h>
# include <string.h>



#define PACKET_PING_SIZE 64
#define HEADERLEN ICMP

typedef struct s_pingpacket
{
        struct icmphdr hdr;
        char msg[PACKET_PING_SIZE-sizeof(struct icmphdr)]; 

}              t_pingpacket;

#endif