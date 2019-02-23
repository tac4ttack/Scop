/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:07:49 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/23 13:23:49 by fmessina         ###   ########.fr       */
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
		{
			if (trash->mesh->vertex)
			{
				ft_putendl("memdel mesh->vertex");
				ft_memdel((void**)&trash->mesh->vertex);
			}
			if (trash->mesh->face)
			{
				ft_putendl("memdel mesh->face");
				ft_memdel((void**)&trash->mesh->face);
			}
			if (trash->mesh->face_format)
			{
				ft_putendl("memdel mesh->face_format");
				ft_memdel((void**)&trash->mesh->face_format);
			}
			if (trash->mesh->normal)
			{
				ft_putendl("memdel mesh->normal");
				ft_memdel((void**)&trash->mesh->normal);
			}
			if (trash->mesh->texture)
			{
				ft_putendl("memdel mesh->texture");
				ft_memdel((void**)&trash->mesh->texture);
			}
			if (trash->mesh->space)
			{
				ft_putendl("memdel mesh->space");
				ft_memdel((void**)&trash->mesh->space);
			}
			if (trash->mesh->line)
			{
				ft_putendl("memdel mesh->line");
				ft_memdel((void**)&trash->mesh->line);
			}
			ft_putendl("memdel mesh");
			ft_memdel((void**)&trash->mesh);
		}
		ft_putendl("memdel trash");
		ft_memdel((void**)&trash);
	}

}
