/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:41:21 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/09 15:56:57 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>

#include "../includes/ft_ls.h"

t_files	*ft_readall(DIR* dir, char *path)
{
	struct dirent *de;
	t_files *file;
	
	file = NULL; 
	while ((de = readdir(dir)) != NULL)
			file = ft_addfile(file, de, path); 
	return (file); 
}

int ft_printall(DIR* dir, unsigned char flags, char *path)
{
	t_files *ptr;
	t_files *files;
	char	*tmpPath;
	char	*tPath;
	DIR*	tmp_dir;
	
	files = ft_readall(dir , path);
	ptr = files;
	if (!(flags & 4))
		ptr = ft_filesort(ptr);
	if (flags & 128)
		ptr = ft_filetimesort(ptr);
	if (flags & 32)
		ptr = ft_revsort(ptr, path);
	if (flags & 8 || flags & 16)
		ft_printlongformat(ptr, flags, path);
	while (ptr != NULL && !(flags & 8 || flags & 16))
	{
		if ((flags & 1 || flags & 4 || ptr->name[0] != '.'))
			ft_putendl(ptr->name);
		ptr = ptr->next;

	}
	ptr = ft_free(files);
	if (flags & 64)
	{
		while (ptr != NULL)
		{
			if ((flags & 1 || flags & 4 || ptr->name[0] != '.'))
				if (ptr->name != NULL && ft_strcmp(ptr->name,".") != 0 && 
						ft_strcmp(ptr->name, "..") != 0 )
				{
					tmpPath = ft_strjoin(path, "/");
					tPath = ft_strjoin(tmpPath, ptr->name);
					ft_strdel(&tmpPath);
					if ((tmp_dir = opendir(tPath)) != NULL)
					{
						ft_printf("%s:\n",tPath);
						ft_printall(tmp_dir, flags, tPath);	
						ft_putchar('\n');
					}
					ft_strdel(&tPath);	
				}
			ptr = ptr->next;
		}
	}
	return (0);
}

unsigned char	ft_flags(char c, unsigned char flags)
{
	if (c == 'a')
		flags |= 1;
	else if (c == 'd')
		flags |= 2;
	else if (c == 'f')
		flags |= 4;
	else if (c == 'g')
		flags |= 8;
	else if (c == 'l')
		flags |= 16;
	else if (c == 'r')
		flags |= 32;
	else if (c == 'R')
		flags |= 64;
	else if (c == 't')
		flags |= 128;
	else if (c == 'G')
		flags |= 256;
	else if (c == 'U')
		flags |= 512;
	else if (c == '1')
		return (flags);
	else
	{
		ft_putstr("ls: illegal option -- ");
		ft_putchar(c);
		ft_putendl("\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]");
		exit(1);
	}
	return (flags);

}

int	main(int ac, char **av)
{
	char 			*str;
	int				loop;
	unsigned char	flags;
	DIR* 			dir;
	t_dir 			*dirs;
	int				eDir;

	loop = 0;
	eDir = 0;
	while (++loop < ac)
	{
		str = av[loop];
		if (*str == '-')
			while (*(++str) != '\0')
				flags = ft_flags(*str, flags);
		else 
		{
			loop--;
			while (++loop < ac)
			{
				eDir = 1;
				if ((dir = opendir(av[loop])))
				{
					dirs = ft_adddir(dirs ,av[loop]);
					closedir(dir);
				}
				else
					ft_printf("ls: %s: No such file or directory\n",av[loop]);
			}
		}
	}
	if (eDir == 0)
	{
		dir = opendir(".");
		ft_printall(dir, flags, ".");
	}
	else
		while (dirs != NULL)
		{
			dir = opendir(dirs->path);	
			ft_printall(dir, flags, dirs->path);
			dirs = dirs->next;
		}
return (0);
}
