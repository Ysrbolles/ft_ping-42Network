

#include "ft_ping.h"

t_params params;

void intHandler(int signum)
{
	params.pingloop = 0;
	printf("\n--- %s ping statistics ---\n", params.Host);
}

void alarmhandler(int signum)
{
	send_packet();
	alarm(1);
}

void start_signal()
{
	signal(SIGALRM, alarmhandler);
	alarmhandler(SIGALRM);
	signal(SIGINT, intHandler);
}
