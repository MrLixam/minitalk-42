/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:38:00 by lvincent          #+#    #+#             */
/*   Updated: 2023/02/22 18:17:37 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <signal.h>
# include "libft/libft.h"

typedef struct s_msg
{
	int		byte;
	int		shift;
	int		len;
	int		cond;
	int		i;
	char	*str;

}	s_msg; 

#endif