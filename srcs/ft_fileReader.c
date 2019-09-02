/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fileReader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 11:28:39 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/13 11:06:19 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static char		ft_filetype(int mode)
{
	mode = (mode & S_IFMT);
	if (S_ISREG(mode))
		return ('-');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISSOCK(mode))
		return ('s');
	else if (S_ISFIFO(mode))
		return ('p');
	else
		return ('-');
}

char			*ft_getattr(struct stat filestat)
{
	char		attr[11];

	attr[0] = ft_filetype(filestat.st_mode);
	attr[1] = ((filestat.st_mode & S_IRUSR) ? 'r' : '-');
	attr[2] = ((filestat.st_mode & S_IWUSR) ? 'w' : '-');
	attr[3] = ((filestat.st_mode & S_IXUSR) ? 'x' : '-');
	attr[4] = ((filestat.st_mode & S_IRGRP) ? 'r' : '-');
	attr[5] = ((filestat.st_mode & S_IWGRP) ? 'w' : '-');
	attr[6] = ((filestat.st_mode & S_IXGRP) ? 'x' : '-');
	attr[7] = ((filestat.st_mode & S_IROTH) ? 'r' : '-');
	attr[8] = ((filestat.st_mode & S_IWOTH) ? 'w' : '-');
	attr[9] = ((filestat.st_mode & S_IXOTH) ? 'x' : '-');
	attr[10] = '\0';
	return (ft_strdup(attr));
}

char			*ft_getgname(struct stat filestat)
{
	struct group	*grp;

	grp = getgrgid(filestat.st_gid);
	if (grp != NULL)
		return (ft_strdup(grp->gr_name));
	else
		return (ft_strdup("root"));
}

char			*ft_getuname(struct stat filestat)
{
	struct passwd	*user;

	user = getpwuid(filestat.st_uid);
	return (ft_strdup(user->pw_name));
}

int				ft_gettotallinks(t_files *files, unsigned int flags)
{
	t_files	*ptr;
	int		total;

	ptr = files;
	total = 0;
	while (ptr != NULL)
	{
		if (flags & 1 || flags & 4 || ptr->name[0] != '.')
			total += ptr->blocks;
		ptr = ptr->next;
	}
	return (total);
}
