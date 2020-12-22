/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:04:29 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/22 22:23:23 by ybolles          ###   ########.fr       */
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

#define PACKET_PING_SIZE 84
#define USEC_TIMEOUT 50000

typedef struct s_pkt
{

	char msg[PACKET_PING_SIZE];
	struct icmphdr hdr;
	struct iphdr ip;

} t_pkt;

typedef struct s_res
{
	struct iovec iov[1];
	struct msghdr msg;
} t_res;

typedef struct s_params
{
	int pingloop;
	int signalalarm;
	struct addrinfo *addr_info;
	struct sockaddr_in *addrinfo;
	int clientsocket;
	struct timeval start_time;
	char addrstr[INET_ADDRSTRLEN];
	char *host;
	int packet_send;
	int msg_count;
	int msg_countrecv;
	t_pkt pkt;
	t_res res;
	struct timeval time_start;
	struct timeval time_end;
	struct timeval tv_out;
	struct timeval tfs;
	struct timeval tfe;
	int ttl;
	int flag;
	int flag_v;
	int interval;
	int daddr;
	long double rtt;
	long double total;
} t_params;

extern t_params g_params;

unsigned short checksum(void *b, int len);
void init_params(void);
void call_ping(void);
void create_sock(void);
void get_packet(void);
void send_packet(void);
void parse_av(int ac, char **av);
int sighandler(int sig);
int get_addrinfo(char *host);

#endif
