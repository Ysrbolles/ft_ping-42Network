


#include "ft_ping.h"

t_params params;

void intHandler(int dummy) 
{ 
	params.pingloop = 0;
} 

void alarmhandler(int i)
{
	printf("----------------------> Khriwa\n");
	send_packet();
	alarm(3);

}

void	start_signal()
{
	signal(SIGALRM, alarmhandler);
	alarm(3);
	signal(SIGINT, intHandler);	
}
