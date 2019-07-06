/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlongformat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 10:03:49 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/06 11:30:37 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void printUser(uid_t uid, gid_t gid, unsigned char flags)
{
	struct passwd *pws;
	struct group *grp;
	pws = getpwuid(uid);
	grp  = getgrgid(gid);
	if (flags & 8)
		printf("%s",grp->gr_name);
	else
		printf("%s\t%s\t", grp->gr_name, pws->pw_name);
}

void	ft_printlongformat(t_files *files, unsigned char flags)
{
    struct stat fileStat;
	char		attr[11];

    if (stat(files->name, &fileStat) < 0)
        printf("File Error Message = %s\n", "FUCK");
    else
	{
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
		printf("%s%4d\t", attr, fileStat.st_nlink);
		printUser(fileStat.st_uid, fileStat.st_gid, flags);
		printf("\n");
	}
}
