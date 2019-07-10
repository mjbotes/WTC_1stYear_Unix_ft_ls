/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 11:45:02 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/10 12:08:40 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

unsigned char	ft_flagscon(char c, unsigned char flags)
{
	if (c == 'R')
		return (flags |= 64);
	else if (c == 't')
		return (flags |= 128);
	else if (c == 'G')
		return (flags |= 256);
	else if (c == 'U')
		return (flags |= 512);
	else if (c == '1')
		return (flags);
	else
	{
		ft_putstr("ft_ls: illegal option -- ");
		ft_putchar(c);
		ft_putendl("\nusage: ls [-RUGadfglrt1] [file ...]");
		exit(1);
	}
	return (flags);
}

unsigned char	ft_flags(char c, unsigned char flags)
{
	if (c == 'a')
		return (flags |= 1);
	else if (c == 'd')
		return (flags |= 2);
	else if (c == 'f')
		return (flags |= 4);
	else if (c == 'g')
		return (flags |= 8);
	else if (c == 'l')
		return (flags |= 16);
	else if (c == 'r')
		return (flags |= 32);
	return (ft_flagscon(c, flags));
}
