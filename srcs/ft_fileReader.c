/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fileReader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 11:28:39 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/06 13:09:11 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	*getAttr(struct stat fileStat)
{
	char		attr[11];

	attr[0] = ((S_ISDIR(fileStat.st_mode)) ? 'd' : '-');
	attr[1] = ((fileStat.st_mode & S_IRUSR) ? 'r' : '-');
	attr[2] = ((fileStat.st_mode & S_IWUSR) ? 'w' : '-');
	attr[3] = ((fileStat.st_mode & S_IXUSR) ? 'x' : '-');
	attr[4] = ((fileStat.st_mode & S_IRGRP) ? 'r' : '-');
	attr[5] = ((fileStat.st_mode & S_IWGRP) ? 'w' : '-');
	attr[6] = ((fileStat.st_mode & S_IXGRP) ? 'x' : '-');
	attr[7] = ((fileStat.st_mode & S_IROTH) ? 'r' : '-');
	attr[8] = ((fileStat.st_mode & S_IWOTH) ? 'w' : '-');
	attr[9] = ((fileStat.st_mode & S_IXOTH) ? 'x' : '-');
	attr[10] = '\0';

	return (ft_strdup(attr));
}

char	*getGName(struct stat fileStat)
{
	struct group	*grp;

	grp = getgrgid(fileStat.st_gid);
	return (ft_strdup(grp->gr_name));
}

char	*getUName(struct stat fileStat)
{
	struct passwd	*user;

	user  = getpwuid(fileStat.st_uid);
	return (ft_strdup(user->pw_name));
}
