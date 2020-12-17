

#include "ft_ping.h"

t_params params;

void intHandler(int signum)
{
	int loss;

	
	params.pingloop = 0;
	loss = 0;
	printf("\n--- %s ping statistics ---\n", params.Host);
	loss = (params.msg_count - params.msg_countrecv) / params.msg_count;
	printf("%d packets transmitted, %d received, %d%% packet loss, time %dms\n", params.msg_count, params.msg_countrecv, loss, params.tfs.tv_usec/ 1000);
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
