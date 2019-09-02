/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dirs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 10:52:47 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/13 11:11:16 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_dir	*ft_newdir(char *path)
{
	t_dir	*new;

	new = malloc(sizeof(t_dir));
	new->next = NULL;
	new->path = ft_strdup(path);
	return (new);
}

t_dir	*ft_adddir(t_dir *dirs, char *path)
{
	t_dir	*ptr;
	t_dir	*new;

	new = ft_newdir(path);
	if (dirs == NULL)
		return (new);
	ptr = dirs;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
	return (dirs);
}

void	ft_deletedirs(t_dir **dirs)
{
	t_dir	*next;
	t_dir	*curr;

	curr = *dirs;
	while (curr)
	{
		next = curr->next;
		ft_strdel(&curr->path);
		curr->next = NULL;
		ft_memdel((void **)&curr);
		curr = next;
	}
	*dirs = NULL;
}
