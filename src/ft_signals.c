


#include "ft_ping.h"

extern int pingloop = 1;

void intHandler(int dummy) 
{ 
    pingloop = 0; 
} 

void	start_signal(void)
{
	
	signal(SIGINT, intHandler);
	printf("--------> after handler (%d)\n" , pingloop);
}
