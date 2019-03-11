/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:07:49 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/11 14:23:45 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"



void	flush(t_scop *trash)
{
	if (trash)
	{
		if (trash->mesh_data)
		{
			ft_putendl("\nmemdel mesh_data");
			ft_memdel((void**)&trash->mesh_data);
		}
		if (trash->mesh)
			mesh_clean(trash->mesh);
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
		if (trash->cam)
		{
			ft_putendl("\nmemdel env->cam");
			ft_memdel((void**)&trash->cam);
		}
		if (trash->uni)
		{
			ft_putendl("\nmemdel env->uni");
			ft_memdel((void**)&trash->uni);

		}
		if (trash->mat)
		{
			ft_putendl("\nmemdel env->mat");
			ft_memdel((void**)&trash->mat);
		}
		// {
		// 	if (trash->mesh->vertex)
		// 	{
		// 		ft_putendl("memdel mesh->vertex");
		// 		ft_memdel((void**)&trash->mesh->vertex);
		// 	}
		// 	if (trash->mesh->face)
		// 	{
		// 		ft_putendl("memdel mesh->face");
		// 		ft_memdel((void**)&trash->mesh->face);
		// 	}
				// 	if (trash->mesh->normal)
		// 	{
		// 		ft_putendl("memdel mesh->normal");
		// 		ft_memdel((void**)&trash->mesh->normal);
		// 	}
		// 	if (trash->mesh->texture)
		// 	{
		// 		ft_putendl("memdel mesh->texture");
		// 		ft_memdel((void**)&trash->mesh->texture);
		// 	}
		// 	if (trash->mesh->space)
		// 	{
		// 		ft_putendl("memdel mesh->space");
		// 		ft_memdel((void**)&trash->mesh->space);
		// 	}
		// 	if (trash->mesh->line)
		// 	{
		// 		ft_putendl("memdel mesh->line");
		// 		ft_memdel((void**)&trash->mesh->line);
		// 	}
		// 	ft_putendl("memdel mesh");
		// 	ft_memdel((void**)&trash->mesh);
		// }
		ft_putendl("memdel win_title");
		ft_memdel((void**)&trash->win_title);
		ft_putendl("memdel trash");
		ft_memdel((void**)&trash);
	}

}
