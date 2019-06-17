/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:07:49 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/17 18:58:37 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"



void	flush(t_scop *trash)
{
	if (trash)
	{
		if (trash->mesh)  // replace with simpleOBJ mesh cleaner?
		 	obj_clean(trash->mesh);
		if (trash->texture)
		{
			if (trash->texture->pixels)
			{
				ft_putendl("\nmemdel env->texture->pixels");
				ft_memdel((void**)&trash->texture->pixels);
			}
			ft_putendl("\nmemdel env->texture");
			ft_memdel((void**)&trash->texture);
		}
		if (trash->world)
		{
			ft_putendl("\nmemdel env->world");
			ft_memdel((void**)&trash->world);
		}
		if (trash->key)
		{
			ft_putendl("\nmemdel env->key");
			ft_memdel((void**)&trash->key);
		}
		if (trash->mouse)
		{
			ft_putendl("\nmemdel env->mouse");
			ft_memdel((void**)&trash->mouse);
		}
		if (trash->uni)
		{
			ft_putendl("\nmemdel env->uni");
			ft_memdel((void**)&trash->uni);

		}


		ft_putendl("memdel win_title");
		ft_memdel((void**)&trash->win_title);
		ft_putendl("memdel trash");
		ft_memdel((void**)&trash);
	}

}
