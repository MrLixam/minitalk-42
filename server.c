/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:12:02 by lvincent          #+#    #+#             */
/*   Updated: 2023/02/22 19:06:57 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void len_calc(s_msg *msg)
{
	msg->len <<= 8;
	msg->len |= msg->byte;
	msg->byte = 0;
	msg->shift = 0;
	msg->cond++;
}

static void msg_reset(s_msg *msg)
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

static void handler(int sig, siginfo_t *info, void *context)
{
	static struct s_msg	msg = { 0 };
	
	msg.byte <<= 1;
	msg.byte |= (sig == SIGUSR1);
	msg.shift++;
	if (msg.shift == 8 && msg.cond < 4)
		len_calc(&msg);
	else if (msg.cond++ == 4)
		msg.str = ft_calloc(msg.len + 1, 1);
	if (msg.shift == 8 && msg.cond > 4 && msg.i < msg.len)
	{
		msg.str[msg.i] |= msg.byte;
		msg.i++;
		kill(info->si_pid, SIGUSR1);
		msg.shift = 0;
		msg.byte = 0;
	}
	if (msg.i == msg.len && msg.cond > 4)
	{
		ft_putstr_fd(msg.str, 1);
		ft_putchar_fd('\n',1);
		msg_reset(&msg);
	}
}

int main()
{
	struct sigaction sa = {0};
	
	ft_printf("my pid is %d\n", getpid());
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while(1)
		continue;
}
