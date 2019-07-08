/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 11:13:18 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/08 13:58:41 by mbotes           ###   ########.fr       */
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
	int				links;
	char			*attr;
	char			*gName;
	char			*uName;
	int				size;
	char			*month;
	char			*day;
	time_t			tTime;
	char			*time;
	int				blocks;
	struct s_files	*next;
	struct s_files	*prev;
}					t_files;

typedef struct		s_dir
{
	char			*path;
	struct s_dir	*next;
}					t_dir;
char			*ft_getUName(struct stat fileStat);
char			*ft_getGName(struct stat fileStat);
char			*ft_getAttr(struct stat fileStat);
t_files			*ft_newfile(struct stat fileStat, struct dirent *de);
t_files			*ft_addfile(t_files *file, struct dirent *de);
t_files			*ft_fileswap(t_files *ptr, t_files *ptr2);
t_files 		*ft_filesort(t_files *files);
t_dir			*ft_newDir(char *path);
t_dir 			*ft_addDir(t_dir *dirs, char *path);
int				ft_maxWidth(t_files *files);
void			ft_printlongformat(t_files *files, unsigned char flags);
void			ft_timeConverter(t_files *new, time_t time);
int				ft_getTotalLinks(t_files *files, unsigned char flags);

#endif
