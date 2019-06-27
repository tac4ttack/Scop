/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:07:49 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/27 17:45:30 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	flush(t_scop *trash)
{
	if (trash)
	{
		if (trash->mesh)
			obj_clean(trash->mesh);
		if (trash->texture)
		{
			if (trash->texture->pixels)
				ft_memdel((void**)&trash->texture->pixels);
			ft_memdel((void**)&trash->texture);
		}
		if (trash->world)
			ft_memdel((void**)&trash->world);
		if (trash->key)
			ft_memdel((void**)&trash->key);
		if (trash->mouse)
			ft_memdel((void**)&trash->mouse);
		if (trash->uni)
			ft_memdel((void**)&trash->uni);
		ft_memdel((void**)&trash->win_title);
		ft_memdel((void**)&trash->prepack_ebo);
		ft_memdel((void**)&trash->prepack_vao);
		ft_memdel((void**)&trash);
	}
}
