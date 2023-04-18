/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:38:11 by lvincent          #+#    #+#             */
/*   Updated: 2023/04/18 20:43:29 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	handler(int sig)
{
	if (sig == SIGUSR2)
		write(1, "Message Received", 17);
}

static void	ft_send_char(int pid, char c)
{
	int	shift;
	int	j;

	shift = 8;
	while (shift--)
	{
		if ((c >> shift) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(5000);
	}
}

static void	ft_send_msg(int pid, char *msg)
{
	int	i;
	int	j;
	int	shift;

	i = 32;
	while (i--)
	{
		if ((ft_strlen(msg) >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(5000);
	}
	i = -1;
	while (msg[++i])
		ft_send_char(pid, msg[i]);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("Invalid use of the command\n");
		ft_printf("format : ./client <server pid> \"Your message\"\n");
		return (-1);
	}
	else if (!ft_strlen(argv[2]))
	{
		ft_printf("The message string must mot be empty\n");
		return (-1);
	}
	if (argv[1] < 0)
	{
		ft_printf("Invalid PID");
		return (-1);
	}
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	ft_send_msg(ft_atoi(argv[1]), argv[2]);
	return (0);
}
