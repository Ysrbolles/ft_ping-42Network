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

#include "../include/ft_ping.h"

int main(){


    int pid = getpid();
    printf("%d\n", pid);
    return 0;
}