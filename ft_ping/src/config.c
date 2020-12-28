#include "../includes/ft_ping.h"

void	sig_handler(int signum)
{
	if (signum == SIGALRM)
		signals.send = 1;
	else if (signum == SIGINT)
		signals.end = 1;
}

void	set_iphdr(t_pckt_infos *state)
{
	state->pckt.ip->version = 4;
	state->pckt.ip->ihl = sizeof(*state->pckt.ip) >> 2;
	state->pckt.ip->ttl = state->ttl;
	state->pckt.ip->protocol = IPPROTO_ICMP;
	inet_pton(AF_INET, state->ipstr, &state->pckt.ip->daddr);
	state->daddr = state->pckt.ip->daddr;
}

void	set_icmphdr(t_pckt_infos *state)
{
	state->pckt.icmp->type = ICMP_ECHO;
	state->pckt.icmp->code = 0;
	state->pckt.icmp->un.echo.id = htons(state->pid);
	state->pckt.icmp->un.echo.sequence = htons(state->seq++);
	state->pckt.icmp->checksum = checksum((unsigned short*)state->pckt.icmp
	, sizeof(struct icmphdr));
}

void	set_response(t_pckt_infos *state)
{
	t_response *res;

	res = &state->response;
	ft_bzero((void*)state->pckt.buf, IPV4_MINIMAL_MTU);
	ft_bzero(res, sizeof(t_response));
	res->iov->iov_base = (void*)state->pckt.buf;
	res->iov->iov_len = sizeof(state->pckt.buf);
	res->msg.msg_iov = res->iov;
	res->msg.msg_iovlen = 1;
	res->msg.msg_name = NULL;
	res->msg.msg_namelen = 0;
	res->msg.msg_flags = MSG_DONTWAIT;
}
