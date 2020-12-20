

#include "ft_ping.h"


void intHandler(int signum)
{
	int loss;

	
	g_params.pingloop = 0;
	loss = 0;
	printf("\n--- %s ping statistics ---\n", g_params.Host);
	loss = (g_params.msg_count - g_params.msg_countrecv) / g_params.msg_count * 100;
	printf("%d packets transmitted, %d received, %d%% packet loss, time %dms\n", g_params.msg_count, g_params.msg_countrecv, loss, g_params.tfs.tv_usec/ 1000);
}

void alarmhandler(int signum)
{
	send_packet();
	ft_sleep(1);
}

void start_signal()
{
	signal(SIGALRM, alarmhandler);
	alarmhandler(SIGALRM);
	signal(SIGINT, intHandler);
}
