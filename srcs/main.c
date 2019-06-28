
#include <dirent.h>

#include "../includes/ft_ls.h"

t_files *ft_newfile(char *name, struct dirent *de)
{
	t_files *new;

	new = malloc(sizeof(t_files));
	new->name = ft_strdup(name);
	new->link = de;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_files	*ft_addfile(t_files *file, char *name, struct dirent *de)
{
	t_files *ptr;
	t_files *new;

	new = ft_newfile(name, de);
	ptr = file;
	if (ptr == NULL)
		file = new;
	else
	{
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
	new->prev = ptr;
	}
	return (file);
}

t_files	*ft_readall()
{
	struct dirent *de;
	DIR *dr;
	t_files *file;
	
	dr = opendir(".");
	file = NULL; 
	while ((de = readdir(dr)) != NULL) 
		file = ft_addfile(file ,de->d_name, de); 
	closedir(dr);
	return (file); 
}

int ft_printall(t_files *files)
{
	t_files *ptr;
	
	ptr = files;
	while (ptr != NULL)
	{
		printf("%-16s", ptr->name);
		ptr = ptr->next;
	}
	printf("\n");
	return (0);
}

void ft_fileswap(t_files *ptr, t_files *ptr2)
{
	if (ptr != NULL)
		ptr->prev->next = ptr2;
	ptr2->prev = ptr->prev;
	ptr->prev = ptr2;
	ptr->next = ptr2->next;
	if (ptr2->next != NULL)
		ptr2->next->prev = ptr;
	ptr2->next = ptr;
}

t_files *ft_filesort(t_files *files)
{
	t_files	*ptr;

	ptr = files;
	while (ptr->next != NULL)
	{
		if (ft_strcmp(ptr->name, ptr->next->name) > 0)
		{
			ft_fileswap(ptr, ptr->next);
			ptr = files;
		}
		else
		ptr = ptr->next;
	}
	return (files);	
}

int	ft_converter(char c, t_files *files)
{
	if (c == 'a')
		return (ft_filesort(files));
	if (c == 'd')
		return (1);
	if (c == 'f')
		return (0);
	if (c == 'g')
		return (3);
	if (c == 'l')
		return (4);
	if (c == 'r')
		return (5);
	if (c == 'R')
		return (6);
	if (c == 'U')
		return (7);
	if (c == 'G')
		return (8);
	if (c == 't')
		return (9);
	return (-1);
}

int	main(int ac, char **av)
{
	char *str;
	t_files	*files;
	if (ac == 2)
	{
		files = ft_readall();
		str = av[1];
		if (*str == '-')
			while (*(++str) != '\0')
				return(ft_converter(*str, files));
	}
return (0);
}
