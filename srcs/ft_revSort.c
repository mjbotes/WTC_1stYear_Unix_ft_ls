/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revSort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbotes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:52:38 by mbotes            #+#    #+#             */
/*   Updated: 2019/07/08 15:59:22 by mbotes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_files	*ft_revSort(t_files files)
{
	t_files *new;
	t_files *ptr;

	ptr = files;
	while (ptr->next != NULL)
		ptr = ptr->next;
	while (ptr != NULL)
		new = addFile(new, ptr->link);

}
