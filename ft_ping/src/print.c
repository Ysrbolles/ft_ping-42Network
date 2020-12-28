#include "../includes/ft_ping.h"
#include <math.h>

void		print_ping(t_pckt_infos *state)
{
	char	*host;
	char	*ip;
	int		payload_s;

	host = state->dest;
	ip = state->ipstr;
	payload_s = IPV4_MINIMAL_MTU - sizeof(struct icmphdr) 
		- sizeof(struct iphdr);
	printf("FT_PING %s (%s) %d(%d) bytes of data.\n", host, ip, payload_s
		, IPV4_MINIMAL_MTU);
}

void		print_stats(t_pckt_infos *state)
{
	int			sended;
	int			reiceved;
	double		pckt_loss;
	long double	avg;
	long double	mdev;

	sended = state->sended;
	reiceved = state->reiceved;
	avg = state->time.avg / sended;
	mdev = (state->time.sum_square / sended) - avg * avg;
	mdev = sqrt(mdev);
	pckt_loss = (sended - reiceved) / sended * 100.0;
	printf("\n--- %s ft_ping statistics ---\n", state->ipstr);
	printf("%d packets transmitted, %d received, %0.1F%% packet loss\n"
		, sended, reiceved, pckt_loss);
	printf("rtt min/avg/max/mdev = %0.3LF/%0.3LF/%0.3LF/%0.3LF ms\n"
		, state->time.min, avg, state->time.max, mdev);
	exit (0);
}

void		print_response(t_pckt_infos *state)
{
	long double	rtt;

	rtt = (state->time.r.tv_usec - state->time.s.tv_usec) / 1000000.0;
	rtt += (state->time.r.tv_sec - state->time.s.tv_sec);
	rtt *= 1000.0;
	state->time.rtt = rtt;
	if (rtt > state->time.max)
		state->time.max = rtt;
	if (rtt < state->time.min || state->time.min == 0.0)
		state->time.min = rtt;
	state->time.avg += rtt;
	state->time.sum_square += rtt * rtt;
	printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%0.2LF ms\n"
		, state->bytes - (int)sizeof(struct iphdr), state->ipstr
		, ntohs(state->pckt.icmp->un.echo.sequence), state->pckt.ip->ttl, rtt);
}

void		print_verbose(t_pckt_infos *state)
{
	char buf[100];

	printf("%d bytes from %s: type = %d code = %d\n"
		, state->bytes - (int)sizeof(struct iphdr)
		, inet_ntop(AF_INET, (void*)&state->pckt.ip->saddr, buf, 100)
		, state->pckt.icmp->type, state->pckt.icmp->code);
}
