/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:38:07 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/03 16:38:09 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int parse_flag(char s)
{
    t_flags flags;
    if (!s)
        return 0;

    if (s == 'v')
    {
        flags.FLAG_V = 1;
        return 1;
    }
    else if (s == 'h')
    {
        flags.FLAG_V = 1;
        return 1;
    }
    else
    {
        printf("ft_ping: invalid option --%c\n", s);
        exit(EXIT_FAILURE);
    }
    return 0;
}

static int socket_loop(struct addrinfo *record)
{
    int ClientSocket;
    //  t_flags flags;

    if (record == NULL)
        return (-1);
    ClientSocket = socket(record->ai_family, record->ai_socktype, record->ai_protocol);
    if (ClientSocket != -1)
    {
        printf(".......................\n");

        return (ClientSocket);
    }
    return (socket_loop(record->ai_next));
}

int main(int ac, char **av)
{
    if (ac < 2)
    {
        fprintf(stderr, "Usage: %s port\n", av[0]);
        exit(EXIT_FAILURE);
    }
    else
    {
        int i;
        int state;

        i = 0;
        if (*av && av[1][0] == '-')
        {
            state = parse_flag(av[1][1]);
            printf("%d\n", state);
        }
        const char *hostName = av[2];
        // const char *portNumber = "https";
        // int ClientSocket;
        struct addrinfo hints;
        ft_memset(&hints, 0, sizeof(struct addrinfo));
        struct addrinfo *results;
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_RAW;
        hints.ai_protocol = IPPROTO_ICMP;
        if ((getaddrinfo(hostName, "https", &hints, &results)) != 0)
        {
            printf("Faied to translate Client Socket.\n");
            exit(EXIT_FAILURE);
        }
        socket_loop(results);
        printf("PING %s : %zu data bytes\n",
               hostName, sizeof(g_pckt));

        // while (record != NULL)
        // {
        //     ClientSocket = socket(record->ai_family, record->ai_socktype, record->ai_protocol);
        //     printf("**********> %d\n", ClientSocket);
        //     if (ClientSocket == -1)
        //         continue;
        //     printf(".......................\n");
        //     con = connect(ClientSocket, record->ai_addr, record->ai_addrlen);
        //     printf("//////////////> %d\n", con);
        //     if (con != -1)
        //         break;
        //     close(ClientSocket);
        //     record = record->ai_next;
        // }
        // if (record == NULL)
        // {
        //     printf("Failed to create or connect Client Socket.\n");
        //     exit(EXIT_FAILURE);
        // }
        // message = "test socket";
        // if (sendto(ClientSocket, message, ft_strlen(message), 0, record->ai_addr, record->ai_addrlen) == -1)
        // {
        //     printf("Failed to perform.\n");
        //     exit(EXIT_FAILURE);
        // }
        // else
        // {
        //     printf("Subliminal message has been planted\n");
        // }
        // close(ClientSocket);
    }
    return 0;
}