/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_timeConverter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 12:57:37 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/08 10:58:50 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_timeConverter(t_files *new, time_t time)
{
	char	*str;
	char	**arr;

	str = ctime(&time);
	arr = ft_strsplit(str, ' ');
	ft_strdel(&arr[0]);
	new->month = ft_strdupdel(&arr[1]);
	new->day = ft_strdupdel(&arr[2]);
	new->time = ft_strndup(arr[3], 5);
	ft_strdel(&arr[4]);

	new->tTime = time;
	//free(arr);
}	
