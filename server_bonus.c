/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:12:02 by lvincent          #+#    #+#             */
/*   Updated: 2023/04/18 20:43:08 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	len_calc(t_msg *msg)
{
	msg->len <<= 8;
	msg->len |= msg->byte;
	msg->byte = 0;
	msg->shift = 0;
	msg->cond++;
}

static void	msg_reset(t_msg *msg)
{
	msg->byte = 0;
	msg->shift = 0;
	msg->len = 0;
	msg->cond = 0;
	msg->i = 0;
	if (msg->str)
		free(msg->str);
	msg->str = NULL;
}

static void	ft_receive_bit(int sig, t_msg *msg)
{
	msg->byte <<= 1;
	msg->byte |= (sig == SIGUSR1);
	msg->shift++;
}

static void	handle(int sig, siginfo_t *info, void *context)
{
	static t_msg	msg = {0};

	(void)context;
	ft_receive_bit(sig, &msg);
	if (msg.shift == 8 && msg.cond < 4)
		len_calc(&msg);
	else if (msg.cond == 4)
	{
		msg.str = ft_calloc(msg.len + 1, 1);
		msg.cond++;
	}
	if (msg.shift == 8 && msg.cond > 4 && msg.i < msg.len)
	{
		msg.str[msg.i] |= msg.byte;
		msg.i++;
		msg.shift = 0;
		msg.byte = 0;
	}
	if (msg.i == msg.len && msg.cond > 4)
	{
		ft_putstr_fd((char *)msg.str, 1);
		msg_reset(&msg);
		kill(info->si_pid, SIGUSR2);
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sig_action;

	ft_printf("my pid is %d\n", getpid());
	sig_action.sa_sigaction = handle;
	sig_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig_action, NULL);
	sigaction(SIGUSR2, &sig_action, NULL);
	while (1)
		continue ;
}
