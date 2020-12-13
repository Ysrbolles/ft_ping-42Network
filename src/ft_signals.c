


#include "ft_ping.h"

extern int pingloop;

void intHandler(int dummy) 
{ 
    pingloop = 0;
} 

void	start_signal(void)
{
	
	signal(SIGINT, intHandler);
	
}
