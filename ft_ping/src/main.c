#include "../includes/ft_ping.h"

static int	get_addresses(char *name, struct addrinfo **res)
{
  struct addrinfo hints;

    bzero(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_RAW;
    hints.ai_protocol = IPPROTO_ICMP;

    if (getaddrinfo(name, NULL, &hints, res) != 0)
        return 1;
    return (0);
}

static void	get_recipient(char *addrstr, t_pckt_infos *states)
{
	struct addrinfo *res;

	 if (get_addresses(addrstr, &res))
        exit_error("Unknown name or service");
	states->rec_in = (struct sockaddr_in*)res->ai_addr;
}

static void	parse_args(int ac, char *av[], t_pckt_infos *state)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			extract_option(av, &i, state);
		}
		else
		{
			get_recipient(av[i], state);
			state->dest = av[i];
			inet_ntop(AF_INET, (void*)&state->rec_in->sin_addr
			, state->ipstr, INET6_ADDRSTRLEN);
			return;
		}
		i++;
	}
}

static void initialize_data(t_pckt_infos *state)
{
	ft_bzero(state, sizeof(t_pckt_infos));
	state->pckt.ip = (struct iphdr*)state->pckt.buf;
	state->pckt.icmp = (struct icmphdr*)(state->pckt.ip + 1);
	state->pid = getpid();
	state->seq = 1;
	state->time.min = 0.0;
	state->time.max = 0.0;
	state->time.sum_square = 0;
	state->ttl = TTL;
	state->count = -1;
	state->interval = 1;
	signals.send = 1;
	signals.end = 0;
}

int			main(int ac, char *av[])
{
	t_pckt_infos	state;

	if (getuid() != 0)
		exit_error("ft_ping: Operation not permitted");
	if (ac < 2)
		exit_usage();
	initialize_data(&state);
	parse_args(ac, av, &state);
	signal(SIGALRM, sig_handler);
	signal(SIGINT, sig_handler);
	ft_ping(&state);
	return (0);
}
