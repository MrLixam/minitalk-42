/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:38:11 by lvincent          #+#    #+#             */
/*   Updated: 2023/04/18 18:51:38 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_send_msg(int pid, char *msg)
{
	int	i;
	int	shift;

	i = 32;
	while (i--)
	{
		if ((ft_strlen(msg) >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
	}
	i = -1;
	while (msg[++i])
	{
		shift = 8;
		while (shift--)
		{
			if ((msg[i] >> shift) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
		}
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("Invalid use of the command\n");
		ft_printf("format : ./client <server pid> \"Your message\"\n");
		return (0);
	}
	if (!ft_strlen(argv[2]))
	{
		ft_printf("The message string must mot be empty\n");
		return (0);
	}
	if (argv[2] < 0)
	{
		ft_printf("Invalid PID");
		return (0);
	}
	ft_send_msg(ft_atoi(argv[1]), argv[2]);
	return (0);
}
