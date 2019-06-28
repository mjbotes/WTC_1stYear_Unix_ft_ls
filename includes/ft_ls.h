

#ifndef FT_LS
# define FT_LS

#include <stdio.h>
#include <dirent.h>
#include "../libft/libft.h"

typedef struct		s_files 
{
	char		*name;
	struct dirent	*link;
	struct s_files	*next;
	struct s_files	*prev;
}			t_files;

t_files			*ft_newfile(char *name, struct dirent *de);
t_files			*ft_addfile(t_files *file, char *name, struct dirent *de);
void			ft_fileswap(t_files *ptr, t_files *ptr2);
t_files 		*ft_filesort(t_files *files);

#endif
