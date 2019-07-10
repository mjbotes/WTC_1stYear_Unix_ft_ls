/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:41:21 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/10 14:58:15 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_files			*ft_readall(DIR *dir, char *path)
{
	struct dirent	*de;
	t_files			*file;

	file = NULL;
	while ((de = readdir(dir)) != NULL)
		file = ft_addfile(file, de, path);
	return (file);
}

void			ft_recursion(char *path, t_files *ptr, unsigned char flags)
{
	char	*tmppath;
	char	*tpath;
	DIR		*tmp_dir;

	while (ptr != NULL)
	{
		if (flags & 1 || flags & 4 || ptr->name[0] != '.')
			if (ptr->name != NULL && ft_strcmp(ptr->name, ".") != 0 &&
				ft_strcmp(ptr->name, "..") != 0)
			{
				tmppath = ft_strjoin(path, "/");
				tpath = ft_strjoin(tmppath, ptr->name);
				ft_strdel(&tmppath);
				if ((tmp_dir = opendir(tpath)) != NULL)
				{
					ft_printf("%s:\n", tpath);
					ft_printall(tmp_dir, flags, tpath);
					ft_putchar('\n');
				}
				ft_strdel(&tpath);
				ft_strdel(&tmppath);
			}
		ptr = ptr->next;
	}
}

int				ft_printall(DIR *dir, unsigned char flags, char *path)
{
	t_files	*ptr;
	t_files	*files;

	files = ft_readall(dir, path);
	ptr = files;
	ptr = ft_sorter(ptr, flags, path);
	if (flags & 8 || flags & 16)
		ft_printlongformat(ptr, flags, path);
	while (ptr != NULL && !(flags & 8 || flags & 16))
	{
		if ((flags & 1 || flags & 4 || ptr->name[0] != '.'))
			ft_putendl(ptr->name);
		ptr = ptr->next;
	}
	closedir(dir);
	if (flags & 64)
		ft_recursion(path, files, flags);
	ft_deletefilelist(files);
	return (0);
}

t_dir			*ft_decrypt(unsigned char *flags, int ac, char **av, int loop)
{
	DIR		*dir;
	int		i;
	t_dir	*dirs;

	dirs = NULL;
	while (++loop < ac)
	{
		i = 1;
		if (av[loop][0] == '-')
			while (av[loop][i] != '\0')
				*flags = ft_flags(av[loop][i++], *flags);
		else if (--loop)
			while (++loop < ac)
			{
				if ((dir = opendir(av[loop])))
				{
					dirs = ft_adddir(dirs, av[loop]);
					closedir(dir);
				}
				else
					ft_nofileerror(av[loop]);
			}
	}
	return (dirs);
}

int				main(int ac, char **av)
{
	unsigned char	flags;
	t_dir			*dirs;

	dirs = NULL;
	dirs = ft_decrypt(&flags, ac, av, 0);
	if (dirs == NULL)
		ft_printall(opendir("."), flags, ".");
	else
		while (dirs != NULL)
		{
			ft_printall(opendir(dirs->path), flags, dirs->path);
			dirs = dirs->next;
		}
	sleep(100);
	return (0);
}
