/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:41:21 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/08 15:52:26 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>

#include "../includes/ft_ls.h"

t_files	*ft_readall(DIR* dir)
{
	struct dirent *de;
	t_files *file;
	
	file = NULL; 
	while ((de = readdir(dir)) != NULL)
		//if ( flags & 1 || de->d_name[0] != '.')
			file = ft_addfile(file, de); 
	return (file); 
}



int ft_printall(DIR* dir, unsigned char flags)
{
	t_files *ptr;
	t_files *files;
	DIR*	tmp_dir;
	int		maxLen;
	
	files = ft_readall(dir);
	ptr = files;
	if (!(flags & 4))
		ptr = ft_filesort(ptr);

	ptr = files;
	maxLen = ft_maxWidth(ptr) + 1;
	maxLen *= -1;
	ptr = files;
	if (flags & 8 || flags & 16)
		ft_printlongformat(ptr, flags);
	while (ptr != NULL && !(flags & 8 || flags & 16))
	{
		if ((flags & 1 || flags & 4 || ptr->name[0] != '.'))
		{
			printf("%s\n", ptr->name);
		}
		ptr = ptr->next;
	}
	if (flags & 64)
	{
		ptr = files;
		while (ptr != NULL)
		{
			if (ptr->name != NULL && ft_strcmp(ft_strdup(ptr->name),ft_strdup(".")) != 0 && 
					ft_strcmp(ft_strdup(ptr->name), ft_strdup("..")) != 0 &&  ptr->link->d_type == 4)
			{
				printf("%s:\n",ptr->name);
				tmp_dir = opendir(ptr->name);
				ft_printall( tmp_dir, flags);
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
	else if (c == 'U')
		flags |= 128;
	else if (c == 'G')
		flags |= 256;
	else if (c == 't')
		flags |= 512;
	else
	{
		printf("%s\n", "usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]");
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
					dirs = ft_addDir(dirs ,av[loop]);
					closedir(dir);
				}
				else
				{
					printf("ls: %s: No such file or directory\n",av[loop]);
				}
			}
		}
	}
	if (eDir == 0)
	{
		dir = opendir(".");
		ft_printall(dir, flags);
	}
	else
		while (dirs != NULL)
		{
			printf("%s:\n", dirs->path);
			dir = opendir(dirs->path);
			ft_printall(dir, flags);
			dirs = dirs->next;
		}
		
return (0);
}
