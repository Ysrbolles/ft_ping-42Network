

#include "ft_ping.h"

t_params g_params;

int get_addrinfo(char *host)
{
	struct addrinfo hints;
	struct addrinfo *servinfo;

	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;

	if (getaddrinfo(host, NULL, &hints, &servinfo) != 0)
		return 1;
	g_params.addr_info = servinfo;
	g_params.addrinfo = (struct sockaddr_in *)servinfo->ai_addr;
	return 0;
}
void parse_av(int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			if (av[i][1] == 'h')
			{
				printf("usage: ./ft_ping [-vh] hostname\n");
				exit(1);
			}
			else if (av[i][1] == 'v')
				g_params.flag_v = 1;
		}
		else
		{
			g_params.host = av[i];
			if (get_addrinfo(av[i]))
			{
				printf("Unknown name or services\n");
				exit(1);
			}
			inet_ntop(AF_INET, &((struct sockaddr_in *)(void *)g_params.addr_info->ai_addr)->sin_addr,
					  g_params.addrstr, sizeof(g_params.addrstr));
			return;
		}
		i++;
	}
}

void init_params()
{
	ft_bzero(g_params, sizeof(t_params));
	g_params.addr_info = sizeof(struct addrinfo);
	g_params.pingloop = 1;
	g_params.signalalarm = 0;
	g_params.pkt.ip = (struct iphdr)g_params.pkt.msg;
	g_params.pkt.hdr = (struct ismphdr)(g_params.pkt.ip + 1);
	g_params.ttl = 63;
	g_params.msg_count = 0;
	g_params.msg_recvcount = 0;
	g_params.interval = 1;
	g_params.flag_v = 0;
	g_params.flag = 1;
}

void create_sock(void)
{
	int sockfd;
	int val;

	val = 1;
	g_params.tv_out.tv_sec = 0;
	g_params.tv_out.tv_usec = USEC_TIMEOUT;
	if (sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP) == -1)
		printf("Socket fd not received\n");
	if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &opt_val, sizeof(int)) < 0)
		exit_error("setsockopt Error");
	g_params.clientsocket = sockfd;
}

void send_packet(void)
{
	ft_bzero((void *)g_params.pkt.msg, PACKET_PING_SIZE);
	g_params.pkt.ip.version = 4;
	g_params.pkt.ip.ihl = sizeof(g_params.pkt.ip) >> 2;
	g_params.pkt.ttl = g_params.tll;
	inet_pton(AF_INET, g_params.addrstr, &g_params.pkt.ip.daddr);
	g_params.daddr = g_params.pkt.ip.daddr;
	g_params.pkt.hdr.type = ICMP_ECHO;
	g_params.pkt.hdr.code = 0;
	g_params.pkt.hdr.un.echo.id = getpid();
	g_params.pkt.hdr.un.echo.sequence = g_params.msg_count++;
	g_params.pkt.hdr.checksum = checksum((unsigned short *)g_params.pkt.hdr, sizeof(struct icmphdr));
	if (sendto(g_params.clientsocket, &g_params.pkt, PACKET_PING_SIZE, 0,
			   g_params.addrinfo, sizeof(struct sockaddr_in)) < 0)
	{
		printf("sendto socket Error\n");
		exit(0);
	}
	if (gettimeofday(&g_params.time_start, NULL) < 0)
	{
		printf("gettimeofday Error\n");
		exit(0);
	}
}

void get_packet()
{
	t_res result;
	int ret;

	result = &g_params.res;
	ft_bzero(g_params.pkt.msg, PACKET_PING_SIZE);
	ft_bzero(result, sizeof(t_res));
	result.iov->iov_base = g_params.pkt.msg;
	result.iov->iov_len = sizeof(g_params.pkt.msg);
	result.msg.msg_iov = result.iov;
	result.msg.msg_iovlen = 1;
	result.msg.msg_name = NULL;
	result.msg.msg_namelen = 0;

	while (!g_params.signalalarm)
	{
		ret = recvmsg(g_params.clientsocket, &g_params.res.msg, MSG_DONTWAIT);
		if (ret > 0)
		{
			if (g_params.pkt.hdr.un.echo.id == getpid())
			{
				if (gettimeofday(&g_params.time_end, NULL) < 0)
				{
					printf("gettimeofday Error\n");
					exit(0);
				}
				g_params.msg_countrecv++;
				g_params.rtt = (g_params.time_end.tv_usec - g_params.time_start.tv_usec) / 1000000.0;
				g_params.rtt += (g_params.time_end.tv_sec - g_params.time_start.tv_sec);
				g_params.rtt *= 1000.0;
				printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.lf ms\n", 64, g_params.addrstr,
					   g_params.msg_count, g_params.ttl, g_params.rtt);
			}
			else if (g_params.flag & FLAG_V)
				printf("%d bytes from %s: type = %d code = %d\n", 64, g_params.addrstr, g_params.pkt.hdr.type, g_params.pkt.hdr.code);
		}
	}
}

void call_ping(void)
{
	create_sock();
	printf("PING %s (%S) 56(84) bytes of data.\n", g_params.host, g_params.addrstr);
	while (g_params.pingloop)
	{
		if (g_params.signalalarm)
		{
			send_packet();
			g_params.signalalarm = 0;
			alarm(g_params.interval);
			get_packet();
		}
	}
}

int sighandler(int sig)
{
	if (sig == SIGINT)
		g_params.pingloop = 0;
	else if (sig == SIGALRM)
		g_params.signalalarm = 1;
}
int main(int ac, char **av)
{
	if (getuid() != 0)
		printf("ft_ping: Operation not permitted\n");
	init_params();
	parse_av(ac, av);
	signal(SIGALRM, sighandler);
	signal(SIGINT, sighandler);
	call_ping();
	return (0);
}
