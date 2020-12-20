


#include "ft_ping.h"

t_params g_params;

int main(int ac, char **av)
{
	struct timeval start;
	struct end;

	init_params();
	if (getuid() != 0)
		printf("ft_ping: Operation not permitted\n");
	if (ac != 2)
	{
		printf("Usage ERROR \n");
		exit(1);
	}
	else
	{

		g_params.Host = av[1];
		if ((g_params.ClientSocket = create_sock()) == -1)
			printf("Socket Failed\n");
		inet_ntop(g_params.addr_info->ai_family, &((struct sockaddr_in *)(void *)g_params.addr_info->ai_addr)->sin_addr, g_params.addrstr, sizeof(g_params.addrstr));
		printf("PING %s (%s) %zu(%zu) bytes of data.\n",
			   av[1], g_params.addrstr,
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