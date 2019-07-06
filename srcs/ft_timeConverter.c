/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_timeConverter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 12:57:37 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/06 13:06:45 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_timeConverter(t_files *new, time_t time)
{
	char	*str;
	char	**arr;

	str = ctime(&time);
	arr = ft_strsplit(str, ' ');
	ft_strdel(&str);
	ft_strdel(&arr[0]);
	new->monthb = ft_strdupdel(&arr[1]);
	new->day = ft_strdupdel(&arr[2]);
	new->time = ft_strhupdel(&arr[5]);
	new->year = ft_strdupdel(&arr[6]);
	free(arr);
}	
