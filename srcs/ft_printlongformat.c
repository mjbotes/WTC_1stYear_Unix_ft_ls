/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlongformat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 10:03:49 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/10 15:41:16 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

size_t	*ft_getformat(t_files *files)
{
	size_t		*arr;
	t_files		*ptr;
	char		*tmp;

	if (!(arr = malloc(sizeof(size_t) * 4)))
		return (NULL);
	ptr = files;
	ft_bzero(arr, 10);
	while (ptr != NULL)
	{
		if (ft_strlen((tmp = ft_itoa(ptr->links))) > arr[0])
			arr[0] = ft_strlen(tmp);
		ft_strdel(&tmp);
		if (ft_strlen(ptr->uname) > arr[1])
			arr[1] = ft_strlen(ptr->uname);
		if (ft_strlen(ptr->gname) > arr[2])
			arr[2] = ft_strlen(ptr->gname);
		if (ft_strlen((tmp = ft_itoa(ptr->size))) > arr[3])
			arr[3] = ft_strlen(tmp);
		ft_strdel(&tmp);
		ptr = ptr->next;
	}
	return (arr);
}

void	ft_linkprint(char *path, t_files *ptr)
{
	char		buffer[65];
	char		*tpath;
	char		*tmp;

	ft_bzero(&buffer, 65);
	tmp = ft_strjoin(path, "/");
	tpath = ft_strjoin(tmp, ptr->name);
	ft_strdel(&tmp);
	readlink(tpath, buffer, 64);
	ft_printf(" -> %s", buffer);
	ft_strdel(&tpath);
}

void	ft_printlongformat(t_files *files, unsigned int flags, char *path)
{
	t_files		*ptr;
	size_t		*arr;
	int 		loop;

	ptr = files;
	arr = ft_getformat(files);
	ft_printf("total %d\n", ft_gettotallinks(files, flags));
	while (ptr != NULL)
	{
		if (flags & 1 || flags & 4 || ptr->name[0] != '.')
		{
			ft_printf("%s%*d", ptr->attr, (int)arr[0] + 2, ptr->links);
			if (flags & 16)
				ft_printf("%*s", (int)arr[1] + 1, ptr->uname);
			ft_printf("%*s%*d%*s", (int)arr[2] + 2, ptr->gname, (int)arr[3] + 2,
					ptr->size, 4, ptr->month);
			ft_printf("%*s%*s %s", 3, ptr->day, 6, ptr->time, ptr->name);
			if (ptr->attr[0] == 'l')
				ft_linkprint(path, ptr);
			ft_putchar('\n');
		}
		ptr = ptr->next;
	}
	loop = 0;
}
