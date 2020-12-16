/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 11:02:32 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/10/09 12:10:50 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ping.h>

void	exit_err(char *s)
{
	printf("%s", s);
	exit(1);
}

void	ft_ping_msg(t_main *p)
{
	p->flag = 1;
	p->pckt = create_msg(&p->msg_count);
	gettimeofday(&p->time_start, NULL);
	(p->msg_count == 1) ? gettimeofday(&p->tfs, NULL) : 0;
}

void	error_report(t_main *p)
{
	if (p->v)
	{
		printf("%d bytes from %s: type = %d code = %d\n",
				PING_PKT_SIZE, p->ip_addr,
				p->pckt.hdr.type, p->pckt.hdr.code);
	}
}
