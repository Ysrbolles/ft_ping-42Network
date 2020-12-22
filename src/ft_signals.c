/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolles <ybolles@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 21:29:00 by ybolles           #+#    #+#             */
/*   Updated: 2020/12/22 21:29:00 by ybolles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "ft_ping.h"

int sighandler(int sig)
{
	if (sig == SIGINT)
		g_params.pingloop = 0;
	else if (sig == SIGALRM)
		g_params.signalalarm = 1;
	return 0;
}