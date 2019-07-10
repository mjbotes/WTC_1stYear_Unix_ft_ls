/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 11:13:18 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/10 13:43:51 by mbotes           ###   ########.fr       */
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

# include "../ft_printf/libft/libft.h"
# include "../ft_printf/include/ft_printf.h"

typedef struct		s_files 
{
	char			*name;
	struct dirent	*link;
	int				links;
	char			*attr;
	char			*gname;
	char			*uname;
	int				size;
	char			*month;
	char			*day;
	time_t			ttime;
	time_t			ctime;
	int				ntime;
	int				cntime;
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

char				*ft_getuname(struct stat fileStat);
char				*ft_getgname(struct stat fileStat);
char				*ft_getattr(struct stat fileStat);
t_files 			*ft_sorter(t_files *ptr, unsigned char flags, char *path);
t_files 			*ft_filesort(t_files *files);
t_files				*ft_revsort(t_files *files, char *path);
t_files 			*ft_filetimesort(t_files *files);
t_dir				*ft_newdir(char *path);
t_dir 				*ft_adddir(t_dir *dirs, char *path);
void				ft_printlongformat(t_files *files, unsigned int flags, char *path);
void				ft_timeconverter(t_files *new, time_t time);
int					ft_gettotallinks(t_files *files, unsigned int flags);
void				ft_filedelete(t_files *file);
t_files				*ft_fileswap(t_files *ptr, t_files *ptr2);
t_files				*ft_addfile(t_files *file, struct dirent *de, char *path);
t_files 			*ft_newfile(struct stat fileStat, struct dirent *de);
t_files				*ft_free(t_files *files);
t_files				*ft_filectimesort(t_files *files);
int					ft_printall(DIR* dir, unsigned char flags, char *path);
unsigned char		ft_flags(char c, unsigned char flags);
void				ft_nofileerror(char *name);

# endif
