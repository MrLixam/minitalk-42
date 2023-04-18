/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:01:48 by lvincent          #+#    #+#             */
/*   Updated: 2023/04/18 20:39:18 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H
# include <signal.h>
# include "libft/libft.h"

typedef struct s_msg
{
	int				byte;
	int				shift;
	int				len;
	int				cond;
	int				i;
	unsigned char	*str;

}	t_msg;

void	handler(int pid);

#endif