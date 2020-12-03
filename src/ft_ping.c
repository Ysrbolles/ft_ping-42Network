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

#include "../ft_ping.h"

int main()
{
    printf("Clinet Server\n");
    const char *Host = "127.0.0.1";
    const char *Port = "6969";
    struct addrinfo hints;
    memset(&hints, 0, sizeof hints);
    struct addrinfo *result;
    struct addrinfo *record;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    int ClinetSocket;

    if ((getaddrinfo(Host, Port, &hints, &result) != 0))
    {
        printf("Faild to translate clinet socket\n");
        exit(EXIT_FAILURE);
    }
    printf("Client Socket Translate");
    for (record = result; record != NULL; record = record->ai_next)
    {
        ClinetSocket = socket(record->ai_family, record->ai_socktype, record->ai_protocol);
        if (ClinetSocket == -1)
            continue;
        if (connect(ClinetSocket, record->ai_addr, record->ai_addrlen) != 1)
            break;
        close(ClinetSocket);
    }
    if (record == NULL)
    {
        printf("Faild to create a connect clinet socket\n");
        exit(EXIT_FAILURE);
    }
    freeaddrinfo(result);
    printf("Client socket Created and Connected");
    return 0;
}