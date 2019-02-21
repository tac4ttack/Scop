/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:07:49 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/21 17:00:34 by fmessina         ###   ########.fr       */
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
			ft_putendl("memdel mesh");
			ft_memdel((void**)&trash->mesh);
		}
		ft_putendl("memdel trash");
		ft_memdel((void**)&trash);
	}

}
