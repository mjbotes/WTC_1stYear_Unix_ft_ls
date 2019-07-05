

#ifndef FT_LS
# define FT_LS

#include <stdio.h>
#include <dirent.h>
#include "../libft/libft.h"

typedef struct		s_files 
{
	char			*name;
	struct dirent	*link;
	struct s_files	*next;
	struct s_files	*prev;
}					t_files;

typedef struct		s_dir
{
	char			*path;
	struct s_dir	*next;
}					t_dir;

t_files			*ft_newfile(char *name, struct dirent *de);
t_files			*ft_addfile(t_files *file, char *name, struct dirent *de);
t_files			*ft_fileswap(t_files *ptr, t_files *ptr2);
t_files 		*ft_filesort(t_files *files);
t_dir			*ft_newDir(char *path);
t_dir 			*ft_addDir(t_dir *dirs, char *path);
int				ft_maxWidth(t_files *files);

#endif
