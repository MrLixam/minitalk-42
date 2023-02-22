/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 21:32:46 by lvincent          #+#    #+#             */
/*   Updated: 2023/02/22 10:59:59 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include "../libft.h"

size_t	ft_format(char c, va_list params);
int		ft_printf(const char *format, ...);
size_t	ft_puthex(unsigned int nbr, char mode);
size_t	ft_putunbr_fd(unsigned int n, int fd);
size_t	ft_putptr(unsigned long long nbr);
size_t	ft_ptr(unsigned long long ptr);
size_t	ft_putchar_fd(char c, int fd);
size_t	ft_putstr_fd(char *s, int fd);
size_t	ft_putnbr_fd(int n, int fd);

#endif