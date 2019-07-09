/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fileSort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 07:24:34 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/09 15:03:39 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_files	*ft_revsort(t_files *files, char *path)
{
	t_files *new;
	t_files *ptr;

	ptr = files;
	new = NULL;
	while (ptr->next != NULL)
		ptr = ptr->next;
	while (ptr != NULL)
	{
		new = ft_addfile(new, ptr->link, path );
		ptr = ptr->prev;
	}
	return (new);
}

t_files *ft_filesort(t_files *files)
{
	t_files	*ptr;

	ptr = files;

	while (ptr->next != NULL)
	{
		if (ft_strcmp(ptr->name, ptr->next->name) > 0)
		{
			ptr = ft_fileswap(ptr, ptr->next);
			ptr = files;
		}
		else
			ptr = ptr->next;
	}
	return (files);
}

t_files *ft_filetimesort(t_files *files)
{
	t_files	*ptr;

	ptr = files;
	while (ptr->next != NULL)
	{
		if (ptr->ttime < ptr->next->ttime)
		{
			ptr = ft_fileswap(ptr, ptr->next);
			ptr = files;
		}
		else if (ptr->ttime == ptr->next->ttime)
		{
			if (ptr->ntime < ptr->next->ntime)
			{
				ptr = ft_fileswap(ptr, ptr->next);
				ptr = files;
			}
			else
				ptr = ptr->next;
		}
		else
			ptr = ptr->next;
	}
	return (files);
}


