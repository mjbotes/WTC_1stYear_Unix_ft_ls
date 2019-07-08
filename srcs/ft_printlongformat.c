/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlongformat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 10:03:49 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/08 15:36:45 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"


size_t	*ft_getFormat(t_files *files)
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
		if (ft_strlen(ptr->uName) > arr[1])
			arr[1] = ft_strlen(ptr->uName);
		if (ft_strlen(ptr->gName) > arr[2])
			arr[2] = ft_strlen(ptr->gName);
		if (ft_strlen(ft_itoa(ptr->size)) > arr[3])
			arr[3] = ft_strlen(ft_itoa(ptr->size));
		ptr = ptr->next;		
	}
	return (arr);
}

void	ft_printlongformat(t_files *files, unsigned char flags)
{
		t_files	*ptr;
		size_t		*arr;

		ptr = files;
		arr = ft_getFormat(files);
		printf("Total: %d\n", ft_getTotalLinks(files, flags));
		while (ptr != NULL)
		{
			if (flags & 1 || flags & 4 || ptr->name[0] != '.')
			{
				printf("%s", ptr->attr);
				printf("%*d",(int)arr[0] + 2, ptr->links);
				if (flags & 16)
					printf("%*s",(int)arr[1] + 1, ptr->uName);
				printf("%*s", (int)arr[2] + 2, ptr->gName);
				printf("%*d", (int)arr[3] + 2,ptr->size);
				printf("%4s", ptr->month);
				printf("%3s", ptr->day);
				printf("%6s ", ptr->time);
				printf("%-1s\n", ptr->name);
			}
			ptr= ptr->next;
		}
}
