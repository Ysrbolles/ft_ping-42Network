

#include "ft_ping.h"

t_params params;

void intHandler(int signum)
{
	params.pingloop = 0;
	printf("\n--- %s ping statistics ---\n", params.Host);
}

void alarmhandler(int signum)
{
	if (signum == SIGALRM)
	{
		printf("----------------------> Khriwa\n");
		send_packet();
		alarm(3);
	}
}

void start_signal()
{
	signal(SIGALRM, alarmhandler);
	alarm(3);
	signal(SIGINT, intHandler);
}
