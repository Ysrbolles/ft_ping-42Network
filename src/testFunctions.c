/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testFunctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 09:24:10 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/06 09:24:12 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int ping(void)
{
    if ((g_env.sock = get_sock()) == -1)
        error(SOCKET, NULL);

    if (g_env.addr_info.ai_family == AF_INET6)
        error(IPV6, NULL);
    if (!inet_ntop(
            g_env.addr_info.ai_family,
            &((struct sockaddr_in *)(void *)g_env.addr_info.ai_addr)->sin_addr,
            g_env.addr_str,
            INET6_ADDRSTRLEN))
        error(INET_NTOP, NULL);

    printf("PING %s (%s) %zu(%zu) bytes of data.\n",
           g_env.opt.host, g_env.addr_str,
           PACKET_DATA_SIZE + sizeof(void *) * 2, sizeof(t_packet) + 20);
    gettimeofday(&g_env.start_time, NULL);
    sig_init(SEC_TO_USEC(g_env.opt.interval) / 1000);
    while (42)
        recv_packet();

    return (PING_ERROR);
}