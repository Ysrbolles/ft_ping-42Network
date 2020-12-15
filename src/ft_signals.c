


#include "ft_ping.h"

t_params *params;

void intHandler(int dummy) 
{ 
    params->pingloop = 0;
} 

void alarmhandler(int i)
{
	if(i == SIGALRM){
		printf("-----> no \n");
	}

}

void	start_signal()
{
	//alarm(2);
	signal(SIGALRM, alarmhandler);
	if (alarm(60) ==  0)
	{
		//alarmhandler(SIGALRM);

	signal(SIGINT, intHandler);
	send_packet();	
	}
}
