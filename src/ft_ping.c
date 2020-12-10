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

int socket_while(struct addrinfo *rp)
{
    int sock;
    t_params params;
    while (rp != NULL)
    {
        if (sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol) == -1)
            continue;
        if (sock != -1)
        {
            params.addr_info = copy(rp);
            printf("\n ++++++++ %d\n", params.addr_info->ai_family);
            return (sock);
        }
        rp = rp->ai_next;
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
    //  printf("\n +++++++++++ \n");
    sockfd = socket_while(servinfo);
    //  printf(" -------> sockfd %d\n" , sockfd);
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
