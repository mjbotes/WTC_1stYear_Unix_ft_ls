/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 11:00:42 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/14 14:45:29 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_files	*ft_newfile(struct stat filestat, struct dirent *de)
{
	t_files	*new;

	new = ft_memalloc(sizeof(t_files));
	new->name = ft_strdup(de->d_name);
	new->link = de;
	new->links = filestat.st_nlink;
	new->attr = ft_getattr(filestat);
	new->gname = ft_getgname(filestat);
	new->uname = ft_getuname(filestat);
	new->size = filestat.st_size;
	new->blocks = filestat.st_blocks;
	ft_timeconverter(new, filestat.st_mtime);
	new->ctime = filestat.st_birthtime;
	new->ntime = filestat.st_mtimespec.tv_nsec;
	new->cntime = filestat.st_birthtimespec.tv_nsec;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_files	*ft_addfile(t_files *file, struct dirent *de, char *path)
{
	t_files			*ptr;
	t_files			*new;
	struct stat		filestat;
	char			*fpath;
	char			*tmp;

	tmp = ft_strjoin(path, "/");
	fpath = ft_strjoin(tmp, de->d_name);
	ft_strdel(&tmp);
	lstat(fpath, &filestat);
	ft_strdel(&fpath);
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

void	ft_deletefilelist(t_files **files)
{
	t_files	*next;
	t_files	*curr;

	curr = *files;
	while (curr != NULL)
	{
		next = curr->next;
		ft_strdel(&curr->name);
		ft_strdel(&curr->attr);
		ft_strdel(&curr->gname);
		ft_strdel(&curr->uname);
		ft_strdel(&curr->month);
		ft_strdel(&curr->day);
		ft_strdel(&curr->time);
		curr->prev = NULL;
		curr->next = NULL;
		ft_memset(curr, 0, sizeof(t_files));
		free(curr);
		curr = next;
	}
	*files = NULL;
}
