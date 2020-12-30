/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:04:29 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/30 09:43:52 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>
# include <netinet/ip_icmp.h>
# include <netdb.h>
# include <sys/time.h>
# include <string.h>
# include <arpa/inet.h>
# include <signal.h>
# include <stdlib.h>

# define USAGE "Usage: ft_ping [-v verbose] [-h help] hostname"
# define PACKET_PING_SIZE 84
# define USEC_TIMEOUT 50000
# define TTL 17
# define FLAG_V 0x02

typedef struct	s_signals
{
	int	send;
	int	end;
}				t_signals;

typedef struct	s_pckt
{
	char			buf[PACKET_PING_SIZE];
	struct iphdr	*ip;
	struct icmphdr	*hdr;
}				t_pckt;

typedef struct	s_res
{
	struct iovec	iov[1];
	struct msghdr	msg;
}				t_res;

typedef struct	s_time
{
	struct timeval	time_start;
	struct timeval	time_end;
	struct timeval	s;
	struct timeval	r;
	long double		rtt;
	long double		min;
	long double		max;
	long double		avg;
	long double		sum_square;
}				t_time;

typedef struct	s_params
{
	t_pckt				pckt;
	struct sockaddr_in	*rec_in;
	char				*host;
	char				addrstr[INET6_ADDRSTRLEN];
	pid_t				pid;
	int					seq;
	int					sockfd;
	int					sended;
	int					reiceved;
	int					bytes;
	t_res				response;
	t_time				time;
	int					ttl;
	int					count;
	int					interval;
	int					daddr;
	unsigned char		flags;
	t_signals			signals;
}				t_params;

extern t_params *g_params;
unsigned short	checksum(unsigned short *data, int len);
void			init_params(void);
void			start_ping(void);
void			create_socket(void);
void			get_packet(void);
void			send_packet(void);
void			parsing(int ac, char **av);
void			sig_handler(int sig);
int				get_addrinfo(char *host);
void			errorstr(char *errorstr);

#endif
