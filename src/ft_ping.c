/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:38:07 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/11 18:26:38 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

struct addrinfo *copy(struct addrinfo *params)
{
    struct addrinfo *on;

    on = malloc(sizeof(struct addrinfo *));

    on->ai_family = params->ai_family;
    on->ai_socktype = params->ai_socktype;
    on->ai_protocol = params->ai_protocol;
    on->ai_addrlen = params->ai_addrlen;
    on->ai_addr = params->ai_addr;
    on->ai_canonname = params->ai_canonname;
    return (on);
}

int socket_while(struct addrinfo *rp, t_params *params)
{
    int sock = 0;
    int i = 0;
    while (rp != NULL)
    {
        sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sock == -1)
        {
            continue;
        }
        if (sock != -1)
        {
            params->addr_info = copy(rp);
            return (sock);
        }
        rp = rp->ai_next;
        i++;
    }
    return (sock);
}

int cerate_sock(char *av, t_params *params)
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;        // Set IP family to IPv4
    hints.ai_socktype = SOCK_RAW;     // Set socket type to RAW
    hints.ai_protocol = IPPROTO_ICMP; // set Protocol to ICMP protocol
    hints.ai_flags = 0;
    printf("Host Name ------> %s\n", av);
    if ((rv = getaddrinfo(av, NULL, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(1);
    }
    int jarb = 0;
    jarb = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    sockfd = socket_while(servinfo, params);
    return (sockfd);
}

int main(int ac, char **av)
{
    t_params params;
    if (ac != 2)
    {
        printf("Usage ERROR \n");
        exit(1);
    }
    else
    {
        if ((params.ClinetSocket = cerate_sock(av[1], &params)) == -1)
            printf("Socket Failed\n");
<<<<<<< HEAD
        char str[INET_ADDRSTRLEN];
        inet_ntop(params.addr_info->ai_family, &((struct sockaddr_in *)(void *)params.addr_info->ai_addr)->sin_addr, str, sizeof(str));
=======
        printf("------------:>%d\n", params.addr_info->ai_family);
        // inet_pton(params.addr_info->ai_family, av[1], &params.addr_info->ai_addr);
        inet_ntop(params.addr_info->ai_family, &((struct sockaddr_in *)(void *)params.addr_info->ai_addr)->sin_addr, params.addrstr, sizeof(params.addrstr));
>>>>>>> aea73784167d691d0fa478b26974cecfd2e280f5

        printf("PING %s (%s) %lu(%lu) bytes of data.\n",
               av[1], params.addrstr,
               PACKET_PING_SIZE, sizeof(t_ping_pkt) + 20);
        gettimeofday(&params.start_time, NULL);
    }
    return (0);
}
