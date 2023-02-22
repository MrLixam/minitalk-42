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

static void handler(int sig)
{
	static struct s_msg	msg = { 0 };
	msg.byte <<= 1;
	msg.byte |= (sig == SIGUSR1);
	msg.shift++;
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
		ft_putstr_fd(msg.str, 1);
		ft_putchar_fd('\n',1);
		msg_reset(&msg);
	}
}

int main()
{
	ft_printf("my pid is %d\n", getpid());
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while(1)
		continue;
}
