/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 11:13:18 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/06 13:15:57 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

# include <stdio.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

#include "../libft/libft.h"

typedef struct		s_files 
{
	char			*name;
	struct dirent	*link;
	char			*attr;
	char			*gName;
	char			*uName;
	int				size;
	char			*month;
	int				*day;
	struct tm		*time;
	struct s_files	*next;
	struct s_files	*prev;
}					t_files;

typedef struct		s_dir
{
	char			*path;
	struct s_dir	*next;
}					t_dir;

t_files			*ft_newfile(struct stat fileStat, struct dirent *de);
t_files			*ft_addfile(t_files *file, char *name, struct dirent *de);
t_files			*ft_fileswap(t_files *ptr, t_files *ptr2);
t_files 		*ft_filesort(t_files *files);
t_dir			*ft_newDir(char *path);
t_dir 			*ft_addDir(t_dir *dirs, char *path);
int				ft_maxWidth(t_files *files);
void			ft_printlongformat(t_files *files, unsigned char flags);
void			ft_timeConverter(t_files *new, time_t time);
char			*getUName(struct stat fileStat);
char			*getGName(struct stat fileStat);
char			*getAttr(struct stat fileStat);

#endif
