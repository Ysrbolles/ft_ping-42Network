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
    return 0;
}

int main(int ac, char **av)
{
    if (ac > 2 && *av)
    {
        // int i;
        // int state;

        // i = 0;
        // if (*av && av[1][0] == '-')
        // {
        //     state = parse_flag(av[1][1]);
        //     printf("%d\n", state);
        // }

        const char *hostName = "www.agoumi.com";
        const char *portNumber = "https";
        int ClientSocket;
        struct addrinfo hints;
        memset(&hints, 0, sizeof(struct addrinfo));
        struct addrinfo *results;
        struct addrinfo *record;
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_RAW;
        hints.ai_protocol = IPPROTO_TCP;
        int con;

        if ((getaddrinfo(hostName, portNumber, &hints, &results)) != 0)
        {
            printf("Faied to translate Client Socket.\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("-------> %d\n", results->ai_family);
        }

        record = results;
        while (record != NULL)
        {
            ClientSocket = socket(record->ai_family, record->ai_socktype, record->ai_protocol);
            printf("**********> %d\n", ClientSocket);
            if (ClientSocket == -1)
                continue;
            printf(".......................\n");
            con = connect(ClientSocket, record->ai_addr, record->ai_addrlen);
            printf("//////////////> %d\n", con);
            if (con != -1)
                break;
            close(ClientSocket);
            record = record->ai_next;
        }
        if (record == NULL)
        {
            printf("Failed to create or connect Client Socket.\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        fprintf(stderr, "Usage: %s port\n", av[0]);
        exit(EXIT_FAILURE);
    }
    return 0;
}