/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freemem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 15:45:11 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/09 16:05:00 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_files	*ft_freeun(t_files *new)
{
	ft_strdel(&new->attr);
	ft_strdel(&new->gname);
	ft_strdel(&new->uname);
	ft_strdel(&new->month);
	ft_strdel(&new->day);
	ft_strdel(&new->time);
	return (new);
}

t_files	*ft_free(t_files *files)
{
	t_files	*ptr;

	ptr = files;
	while (ptr != NULL)
	{
		ptr = ft_freeun(ptr);
		ptr = ptr->next;
		free(ptr->prev);
	}
	return (files);
}
