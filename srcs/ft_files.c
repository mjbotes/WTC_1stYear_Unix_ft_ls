/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 11:00:42 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/09 15:04:50 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_files *ft_newfile(struct stat filestat, struct dirent *de)
{
	t_files *new;

	new = malloc(sizeof(t_files));
	new->name = ft_strdup(de->d_name);
	new->link = de;
	new->links = filestat.st_nlink;
	new->attr = ft_getattr(filestat);
	new->gname = ft_getgname(filestat);
	new->uname = ft_getuname(filestat);
	new->size = filestat.st_size;
	new->blocks = filestat.st_blocks;
	ft_timeconverter(new, filestat.st_mtime);
	new->ntime = filestat.st_mtimespec.tv_nsec;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_files	*ft_addfile(t_files *file, struct dirent *de, char *path)
{
	t_files			*ptr;
	t_files 		*new;
	struct stat		filestat;
	char			*fPath;
	char			*tmp;
	
	tmp = ft_strjoin(path, "/");
	fPath = ft_strjoin(tmp, de->d_name);
	ft_strdel(&tmp);
	lstat(fPath, &filestat);
	new = ft_newfile(filestat, de);
	ptr = file;
	if (ptr == NULL)
		return (new);
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

void	ft_filedelete(t_files *file)
{
	ft_strdel(&file->name);
	file->link = NULL;
	file->links = 0;
	ft_strdel(&file->attr);
	ft_strdel(&file->gname);
	ft_strdel(&file->uname);
	file->size = 0;
	file->blocks = 0;
	file->next = NULL;
	file->prev = NULL;
}

void	ft_deletefilelist(t_files *files)
{
	t_files	*ptr;

	ptr = files;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		ft_filedelete(files);
		files = ptr;
	}
}
