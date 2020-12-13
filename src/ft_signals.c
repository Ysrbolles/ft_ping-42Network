


#include "ft_ping.h"

extern int pingloop;

void intHandler(int dummy) 
{ 
    pingloop = 0;
} 

void	start_signal(t_params *params)
{
	
	signal(SIGINT, intHandler);
	send_packet(params);	
}
