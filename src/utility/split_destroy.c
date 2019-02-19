/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 17:55:18 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/19 17:56:24 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	split_destroy(char **split)
{
	char **tmp;

	tmp = split;
	if (*split)
	{
		while (*split)
			ft_memdel((void**)split++);
		ft_memdel((void**)(&tmp));
	}
}
