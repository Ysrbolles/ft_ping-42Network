

#include "ft_ping.h"

t_params g_params;

void	parse_av(int ac, char **av)
{
	if(ac > 3)
	{
		printf("usage: ./ft_ping [-vh] hostname\n");
		exit(1);
	}

	if(ac == 1 || (ac == 2 && av[1][0] == '-' && av[1][1] == 'h'))
	{
		printf("usage: ./ft_ping [-vh] hostname\n");
		exit(1);
	}
	if ((ac == 3 && av[1][0] == '-'
				&& av[1][1] == 'h' && av[1][2] == '\0'))
	{
		printf("usage: ./ft_ping [-vh] hostname\n");
		exit(0);
	}

	if(ac == 3 && av[1][0] == '-' && av[1][1] == 'v')
		g_params.flag_v = 1;
	if(ac == 2 && g_params.flag_v)
	{
		printf("usage: ./ft_ping [-vh] hostname\n");
		exit(1);	
	}	
}

int main(int ac, char **av)
{
	struct timeval start;
	struct end;

	init_params();
	if (getuid() != 0)
		printf("ft_ping: Operation not permitted\n");

	parse_av(ac, av);
	if(ac == 3 && av[2] || ac == 2)
	{


		g_params.Host = ac == 3 ? av[2] : av[1];
		if ((g_params.ClientSocket = create_sock()) == -1)
			printf("Socket Failed\n");
		inet_ntop(g_params.addr_info->ai_family, &((struct sockaddr_in *)(void *)g_params.addr_info->ai_addr)->sin_addr, g_params.addrstr, sizeof(g_params.addrstr));
		printf("PING %s (%s) %zu(%zu) bytes of data.\n",
				g_params.Host, g_params.addrstr,
				56, 58);
		start_signal();
		while (g_params.pingloop)
		{
			get_packet();
			ft_sleep(1);
		}
	}
	return (0);
}

