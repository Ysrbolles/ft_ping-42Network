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

# define USAGE "Usage: ft_ping [-v verbose] [-h help] destination"

# define IPV4_MINIMAL_MTU 84

# define USEC_TIMEOUT 50000
# define TTL 17
# define FLAG_C 0x01
# define FLAG_V 0x02
# define FLAG_I 1 << 2

typedef struct			s_signals
{
	int					send;
	int					end;
}						t_signals;

t_signals				signals;

typedef struct			s_pckt
{
	char				buf[IPV4_MINIMAL_MTU];
	struct iphdr		*ip;
	struct icmphdr		*icmp;
}						t_pckt;

typedef struct			s_response
{
	struct iovec		iov[1];
	struct msghdr		msg;
}						t_response;

typedef struct			s_time
{
	struct timeval		s;
	struct timeval		r;
	long double			rtt;
	long double			min;
	long double			max;
	long double			avg;
	long double			sum_square;
}						t_time;

typedef struct			s_pckt_infos
{
	t_pckt				pckt;
	struct sockaddr_in	*rec_in;
	char				*dest;
	char				ipstr[INET6_ADDRSTRLEN];
	pid_t				pid;
	int					seq;
	int					sockfd;
	int					sended;
	int					reiceved;
	int					bytes;
	t_response			response;
	t_time				time;
	int					ttl;
	int					count;
	int					interval;
	int					daddr;
	unsigned char		flags;
}						t_pckt_infos;


unsigned short			checksum(unsigned short *data, int len);
void					ft_bzero(void *data, size_t len);
void					exit_error(char *error);
void					set_iphdr(t_pckt_infos *state);
void					set_icmphdr(t_pckt_infos *state);
void					ft_ping(t_pckt_infos *state);
void					open_raw_socket(t_pckt_infos *state);
void					set_response(t_pckt_infos *state);
void					sig_handler(int signum);
void					print_response(t_pckt_infos *state);
void					print_ping(t_pckt_infos *state);
void					print_stats(t_pckt_infos *state);
int						ft_atoi(const char *str);
void					extract_option(char*av[], int *i, t_pckt_infos *state);
void					print_verbose(t_pckt_infos *state);
void					exit_usage();


#endif
