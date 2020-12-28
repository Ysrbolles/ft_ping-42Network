#include "../includes/ft_ping.h"

void			open_raw_socket(t_pckt_infos *state)
{
    int 			sockfd;
	int				opt_val;
	struct timeval	tv_out;

	opt_val = 1;
	tv_out.tv_sec = 0;
	tv_out.tv_usec = USEC_TIMEOUT;
    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
        exit_error("Socket file descriptor not received!!");
	if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &opt_val, sizeof(int)) < 0)
		exit_error("setsockopt Error");
    state->sockfd = sockfd;
}

unsigned short	checksum(unsigned short *data, int len)
{
	unsigned long	checksum;

	checksum = 0;
	while (len > 1)
	{
		checksum = checksum + *data++;
		len = len - sizeof(unsigned short);
	}
	if (len)
		checksum = checksum + *(unsigned char*)data;
	checksum = (checksum >> 16) + (checksum & 0xffff);
	checksum = checksum + (checksum >> 16);
	return (unsigned short)(~checksum);
}

void			exit_usage()
{
	printf("Usage: ft_ping [-v verbose] [Options] destination\n"
	"			---		Options		---\n"
	"	-v			display result when other ICMP packet receives\n"
	"	-c Number	stop after sending Number packets\n"
	"	-t Number	set the ttl to Number\n"
	"	-i Number	wait Number second between sending each packet\n"
	"	-h			display this usage\n"
	);
	exit(0);
}

void			exit_error(char *error)
{
	printf("ft_ping: %s\n", error);
	exit(0);
}

void			ft_bzero(void *data, size_t len)
{
	int		i;
	char	*bits;

	i = 0;
	bits = (char*)data;
	while (i < len)
	{
		bits[i] = 0;
		i++;
	}
}
