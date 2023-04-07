/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:38:11 by lvincent          #+#    #+#             */
/*   Updated: 2023/02/22 18:19:16 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int sig_wait = 0;

void handler(int sig)
{
	if (sig == SIGUSR1)
		sig_wait = 1;
}	

static void ft_send_char(int pid, char c)
{
	while(c)
	{
		if (c & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		c >>= 1;
		while (!sig_wait)
			continue ;
		sig_wait = 0;
	}
}

static void ft_send_msg(int pid, char *msg)
{
	int i;
	int len;

	len = ft_strlen(msg);
	i = 32;
	while (i--)
	{
		if ((len >> i) & 1)
			kill(pid,SIGUSR1);
		else
			kill(pid,SIGUSR2);
		while (!sig_wait)
			continue;
		sig_wait = 0;
	}
	i = -1;
	while (msg[++i])
		send_char(pid, msg[i]);
	send_char(pid, '\0');
}

int main(int argc, char** argv)
{
	if (argc != 3 || !ft_strlen(argv[2]))
	{
		ft_printf("Invalid use of the command\n");
		ft_printf("format : ./client <server pid> \"Your message\"\n");
		ft_printf("The message string must mot be empty\n");
		return (0);
	}
	signal(SIGUSR1, handler);
	ft_send_msg(ft_atoi(argv[1]), argv[2]);
}
