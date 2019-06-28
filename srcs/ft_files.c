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
