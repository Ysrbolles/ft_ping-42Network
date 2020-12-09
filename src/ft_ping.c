/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:38:07 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/09 15:43:53 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int main(int ac, char **av)
{
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

        int sockfd;
        struct addrinfo hints, *servinfo, *p;
        int rv;

        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_INET;    // Set IP family to IPv4
        hints.ai_socktype = SOCK_RAW; // Set socket type to stream
        hints.ai_protocol = IPPROTO_ICMP;
        hints.ai_flags = 0;
        printf("Host Name ------> %s\n", av[1]);
        if ((rv = getaddrinfo(av[1], NULL, &hints, &servinfo)) != 0)
        {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
            exit(1);
        }
        p = servinfo;
        while ((p->ai_next != NULL))
        {
            if ((sockfd = socket(p->ai_family, p->ai_socktype,
                                 p->ai_protocol)) == -1)
                continue;
        }
        // loop through all the results and connect to the first we can
        if (p == NULL)
        {
            // looped off the end of the list with no connection
            fprintf(stderr, "failed to connect\n");
            exit(2);
        }
        printf("%d\n", sockfd);
        char str[INET_ADDRSTRLEN];
        inet_pton(p->ai_family, av[1], &(p->ai_addr));
        // printf(" ---------> %s\n", inet_pton(p->ai_family, av[1], &(p->ai_addr)));
        inet_ntop(p->ai_family, &(p->ai_addr), str, sizeof(str));
        printf(" ---------> %s\n", str);
    }
}
