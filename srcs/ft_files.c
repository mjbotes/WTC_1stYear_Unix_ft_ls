/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 11:00:42 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/08 15:58:47 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_files *ft_newfile(struct stat fileStat, struct dirent *de)
{
	t_files *new;

	new = malloc(sizeof(t_files));
	new->name = ft_strdup(de->d_name);
	new->link = de;
	new->links = fileStat.st_nlink;
	new->attr = ft_getAttr(fileStat);
	new->gName = ft_getGName(fileStat);
	new->uName = ft_getUName(fileStat);
	new->size = fileStat.st_size;
	new->blocks = fileStat.st_blocks;
	ft_timeConverter(new, fileStat.st_mtime);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_files	*ft_addfile(t_files *file, struct dirent *de)
{
	t_files		*ptr;
	t_files 	*new;
	struct stat	filestat;
	
	stat(de->d_name, &filestat);
	new = ft_newfile(filestat, de);
	ptr = file;
	if (ptr == NULL)
		file = new;
	else
	{
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
	new->prev = ptr;
	}
	return (file);
}

t_files	*ft_fileswap(t_files *ptr, t_files *ptr2)
{
	if (ptr->prev != NULL)
		ptr->prev->next = ptr2;
	ptr2->prev = ptr->prev;
	ptr->prev = ptr2;
	ptr->next = ptr2->next;
	if (ptr2->next != NULL)
		ptr2->next->prev = ptr;
	ptr2->next = ptr;
	return (ptr2);
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

void	ft_filedelete
