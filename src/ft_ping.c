/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:38:07 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/08 21:55:25 by ybolles          ###   ########.fr       */
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
        hints.ai_family = AF_INET;       // Set IP family to IPv4
        hints.ai_socktype = SOCK_RAW; // Set socket type to stream
        hints.ai_protocol = IPPROTO_TCP;
        // hints.ai_protocol = IPPROTO_ICMP;
        printf("Host Name ------> %s\n", av[1]);
        if ((rv = getaddrinfo(av[1], "https", &hints, &servinfo)) != 0)
        {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
            exit(1);
        }

        // loop through all the results and connect to the first we can
        for (p = servinfo; p != NULL; p = p->ai_next)
        {
            if ((sockfd = socket(p->ai_family, p->ai_socktype,
                                 p->ai_protocol)) == -1)
            {
                perror("socket");
                continue;
            }

            if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
            {
                perror("connect");
                close(sockfd);
                continue;
            }

            break; // if we get here, we must have connected successfully
        }

        if (p == NULL)
        {
            // looped off the end of the list with no connection
            fprintf(stderr, "failed to connect\n");
            exit(2);
        }
        char str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, p->ai_addr, str, p->ai_addrlen);
        printf(" ---------> %s\n", str);
    }
}
