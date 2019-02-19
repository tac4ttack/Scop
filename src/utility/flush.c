/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:07:49 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/19 17:33:37 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	flush(t_scop *trash)
{
	if (trash)
	{
		ft_putendl("\nmemdel mesh_data");
		ft_memdel((void**)&trash->mesh_data);

		ft_putendl("memdel mesh->vertex");
		ft_memdel((void**)&trash->mesh->vertex);

		ft_putendl("memdel mesh");
		ft_memdel((void**)&trash->mesh);

		// if (trash->mesh)
			// mesh_destroy(trash->mesh);
			// ft_memdel(trash->mesh);
		// GLFW and GLEW cleaning
	}
	ft_putendl("memdel trash");
	ft_memdel((void**)&trash);
}
