/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlongformat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 10:03:49 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/09 15:44:55 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"


size_t	*ft_getformat(t_files *files)
{
	size_t		*arr;
	t_files	*ptr;

	if (!(arr = malloc(sizeof(size_t) * 10)))
			return (NULL);
	ptr = files;
	ft_bzero(arr, 10);
	while (ptr != NULL)
	{
		if (ft_strlen(ft_itoa(ptr->links)) > arr[0])
			arr[0] = ft_strlen(ft_itoa(ptr->links));
		if (ft_strlen(ptr->uname) > arr[1])
			arr[1] = ft_strlen(ptr->uname);
		if (ft_strlen(ptr->gname) > arr[2])
			arr[2] = ft_strlen(ptr->gname);
		if (ft_strlen(ft_itoa(ptr->size)) > arr[3])
			arr[3] = ft_strlen(ft_itoa(ptr->size));
		ptr = ptr->next;		
	}
	return (arr);
}

void	ft_printlongformat(t_files *files, unsigned int flags, char *path)
{
		t_files	*ptr;
		size_t		*arr;
		char		buffer[65];
		char		*tPath;
		char		*tmp;

		ptr = files;
		arr = ft_getformat(files);
		ft_printf("total %d\n", ft_gettotallinks(files, flags));
		while (ptr != NULL)
		{
			if (flags & 1 || flags & 4 || ptr->name[0] != '.')
			{
				ft_printf("%s", ptr->attr);
				ft_printf("%*d",(int)arr[0] + 2, ptr->links);
				if (flags & 16)
					ft_printf("%*s",(int)arr[1] + 1, ptr->uname);
				ft_printf("%*s", (int)arr[2] + 2, ptr->gname);
				ft_printf("%*d", (int)arr[3] + 2,ptr->size);
				ft_printf("%4s", ptr->month);
				ft_printf("%3s", ptr->day);
				ft_printf("%6s ", ptr->time);
				ft_printf("%-1s", ptr->name);
				if (ptr->attr[0] == 'l')
				{
					ft_bzero(&buffer, 129);
					tmp = ft_strjoin(path, "/");
					tPath = ft_strjoin(tmp, ptr->name);
					ft_strdel(&tmp);
					readlink(tPath, buffer, 128);
					ft_printf(" -> %s", buffer);
					ft_strdel(&tPath);
				}
				ft_putchar('\n');
			}
			ptr= ptr->next;
		}
}
