/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 17:55:18 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/27 17:45:16 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

size_t		split_len(char **split)
{
	size_t	ret;

	if (split)
	{
		ret = 0;
		while (*split)
		{
			ret++;
			split++;
		}
		return (ret);
	}
	return (0);
}

void		split_destroy(char **split)
{
	char	**tmp;

	tmp = split;
	if (*split)
	{
		while (*split)
			ft_memdel((void**)split++);
		ft_memdel((void**)(&tmp));
	}
}
