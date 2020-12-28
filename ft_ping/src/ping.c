#include "../includes/ft_ping.h"
#include<errno.h>

static void	get_pong(t_pckt_infos *state)
{
	int bytes;

	set_response(state);
	while (!signals.send)
	{
		bytes = recvmsg(state->sockfd, &(state->response.msg), MSG_DONTWAIT);
		if (bytes > 0)
		{
			state->bytes = bytes;
			if (state->pckt.icmp->un.echo.id == ntohs(state->pid))
			{
				if (gettimeofday(&state->time.r, NULL) < 0)
					exit_error("gettimeofday Error");
				state->reiceved++;
				print_response(state);
			} else if (state->flags & FLAG_V)
				print_verbose(state);
			return ;
		}
	}
}

static void	send_ping(t_pckt_infos * state)
{
	ft_bzero((void*)state->pckt.buf, IPV4_MINIMAL_MTU);
	set_iphdr(state);
	set_icmphdr(state);
	if (sendto(state->sockfd, (void*)&state->pckt, IPV4_MINIMAL_MTU, 0
	, (void*)state->rec_in, sizeof(struct sockaddr_in)) < 0)
		exit_error("sendto Error");
	if (gettimeofday(&state->time.s, NULL) < 0)
		exit_error("gettimeofday Error");
	state->sended++;
}

static int	is_finish(t_pckt_infos *state)
{
	if (signals.end)
		return (1);
	if (state->count == 0)
		return (1);
	return (0);
}

void		ft_ping(t_pckt_infos *state)
{
	open_raw_socket(state);
	print_ping(state);
	while (!is_finish(state))
	{
		if (signals.send)
		{
			send_ping(state);
			signals.send = 0;
			alarm(state->interval);
			get_pong(state);
			if (state->flags & FLAG_C)
				state->count--;
		}
	}
	print_stats(state);
}
