/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:38:07 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/10 14:54:20 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int socket_while(struct addrinfo *rp)
{
    int sock;
    t_params params;

    while (rp != NULL)
    {
        if (sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol) == -1)
            continue;
        printf(" Sock --------> %d\n", sock);

        if (sock != -1)
        {
            ft_memcpy(&params.addr_info, rp, sizeof(struct addrinfo));
            return (sock);
        }
        rp->ai_next;
    }

    return (sock);
}

int cerate_sock(char *av)
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
    sockfd = socket_while(servinfo);

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
        // code for a client connecting to a server
        // namely a stream socket to www.example.com on port 80 (http)
        // either IPv4 or IPv6
        if ((params.ClinetSocket = cerate_sock(av[1])) == -1)
            printf("Socket Failed\n");
        else
            printf("%d\n", params.ClinetSocket);
        // char str[INET_ADDRSTRLEN];
        // inet_pton(params->addr_info->ai_family, av[1], &params->addr_info->ai_addr);
        // // printf(" ---------> %s\n", inet_pton(p->ai_family, av[1], &(p->ai_addr)));
        // inet_ntop(params->addr_info->ai_family, &(params->addr_info->ai_addr), str, sizeof(str));
        // printf(" ---------> %s\n", str);
    }
}
