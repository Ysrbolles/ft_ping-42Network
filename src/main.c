

#include "ft_ping.h"

t_params g_params;

void parse_av(int ac, char **av)
{
	int	i;

	i = 1;
	while( i < ac)
	{
		if(av[i][0] == '-')
		{
			if(av[i][1] == 'h')
			{
				printf("usage: ./ft_ping [-vh] hostname\n");
				exit(1);
			}
			else if(av[i][1] == 'v')
				g_params.flag_v = 1;
		}
		else 
		{
			get_addrinfo(av[i]);
			g_params.Host = av[i];
			inet_ntop(AF_INET, &((struct sockaddr_in *)(void *)g_params.addr_info->ai_addr)->sin_addr,
					g_params.addrstr, sizeof(g_params.addrstr));
			return ;
		}
		i++;
	}
}

void	init_params()
{
	ft_bzero(g_params, sizeof(t_params));
	g_params.pingloop = 1;
	g_params.pkt.ip = (struct iphdr)g_params.pkt.msg;
	g_params.pkt.hdr = (struct ismphdr)(g_params.pkt.ip+1);
	g_params.ttl = 63;
	g_params.msg_count = 0;
	g_params.msg_recvcount = 0;
	g_params.interval = 1;
	g_params.flag_v = 0;
	g_params.flag = 1;
}

int main(int ac, char **av)
{
	if (getuid() != 0)
		printf("ft_ping: Operation not permitted\n");
	init_params();
	parse_av(ac, av);
	signal(SIGALRM, sighandler);
	signal(SIGINT, sighandler);
	call_ping();
	return (0);
}
