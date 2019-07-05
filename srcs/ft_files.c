/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 11:00:42 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/05 14:45:21 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_files *ft_newfile(char *name, struct dirent *de)
{
	t_files *new;

	new = malloc(sizeof(t_files));
	new->name = ft_strdup(name);
	new->link = de;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_files	*ft_addfile(t_files *file, char *name, struct dirent *de)
{
	t_files *ptr;
	t_files *new;

	new = ft_newfile(name, de);
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
	char *tmp;
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

int ft_maxWidth(t_files *files)
{
	int len;
	t_files	*ptr;

	len = 15;
	ptr = files;
	while (ptr != NULL)
	{
		if (len < ft_strlen(ptr->name))
			len = ft_strlen(ptr->name);
		ptr = ptr->next;
	}
	return (len);
}
