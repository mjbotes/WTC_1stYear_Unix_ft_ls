/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fileSort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 07:24:34 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/10 13:46:46 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_files	*ft_sorter(t_files *ptr, unsigned char flags, char *path)
{
	if (!(flags & 4))
		ptr = ft_filesort(ptr);
	if (flags & 128)
		ptr = ft_filetimesort(ptr);
	if (flags & 512)
		ptr = ft_filectimesort(ptr);
	if (flags & 32)
		ptr = ft_revsort(ptr, path);
	return (ptr);
}

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
		new = ft_addfile(new, ptr->link, path);
		ptr = ptr->prev;
	}
	return (new);
}

t_files	*ft_filesort(t_files *files)
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

t_files	*ft_filetimesort(t_files *files)
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

t_files	*ft_filectimesort(t_files *files)
{
	t_files	*ptr;

	ptr = files;
	while (ptr->next != NULL)
	{
		if (ptr->ctime < ptr->next->ctime)
		{
			ptr = ft_fileswap(ptr, ptr->next);
			ptr = files;
		}
		else if (ptr->ctime == ptr->next->ctime)
		{
			if (ptr->cntime < ptr->next->cntime)
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
