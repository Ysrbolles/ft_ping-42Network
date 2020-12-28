#include "../includes/ft_ping.h"

static int	get_value_opt(char *value, char *error)
{
	int	ret;

	if (!value)
		exit_error("value missing");
	ret = ft_atoi(value);
	if (ret == 0)
		exit_error(error);
	return ret;
}

void	extract_option(char*av[], int *i, t_pckt_infos *state)
{
	int		opt;

	opt = av[*i][1];
	if (opt == 'h')
		exit_usage();
	else if (opt == 'v')
		state->flags |= FLAG_V;
	else if (opt == 't')
		state->ttl = get_value_opt(av[++(*i)]
			, "can't set unicast time-to-live: Argument invalide");
	else if (opt == 'c')
	{
		state->flags |= FLAG_C;
		state->count = get_value_opt(av[++(*i)]
			, "bad number of packets to transmit.");
	}
	else if (opt == 'i')
	{
		state->flags |= FLAG_I;
		state->interval = get_value_opt(av[++(*i)], "bad timing interval.");
	}
	else
		exit_usage();
}
