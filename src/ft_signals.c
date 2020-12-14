


#include "ft_ping.h"

extern int pingloop;

void intHandler(int dummy) 
{ 
    pingloop = 0;
} 

void alarmhandler(int i)
{
	if(i == SIGALRM){
		printf("-----> no \n");
	}

}

void	start_signal(t_params *params)
{
	//alarm(2);
	signal(SIGALRM, alarmhandler);
	if (alarm(60) ==  0)
	{
		//alarmhandler(SIGALRM);

	signal(SIGINT, intHandler);
	send_packet(params);	
	}
}
