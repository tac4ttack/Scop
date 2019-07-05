/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_prepack_get_center_axis.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 12:38:16 by fmessina          #+#    #+#             */
/*   Updated: 2019/07/05 12:38:16 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	center_x_axis(t_obj *mesh, size_t i)
{
	if (mesh)
	{
		mesh->vertex[i] < mesh->axis[0].x ? \
			mesh->axis[0].x = mesh->vertex[i] : 0;
		mesh->vertex[i] > mesh->axis[1].x ? \
			mesh->axis[1].x = mesh->vertex[i] : 0;
	}
}

static void	center_y_axis(t_obj *mesh, size_t i)
{
	if (mesh)
	{
		mesh->vertex[i + 1] < mesh->axis[0].y ? \
			mesh->axis[0].y = mesh->vertex[i + 1] : 0;
		mesh->vertex[i + 1] > mesh->axis[1].y ? \
			mesh->axis[1].y = mesh->vertex[i + 1] : 0;
	}
}

static void	center_z_axis(t_obj *mesh, size_t i)
{
	if (mesh)
	{
		mesh->vertex[i + 2] < mesh->axis[0].z ? \
			mesh->axis[0].z = mesh->vertex[i + 2] : 0;
		mesh->vertex[i + 2] > mesh->axis[1].z ? \
			mesh->axis[1].z = mesh->vertex[i + 2] : 0;
	}
}

bool		get_center_axis(t_obj *mesh)
{
	size_t	i;

	i = 0;
	if (mesh)
	{
		while (i < mesh->n_vertex[0] * 8)
		{
			center_x_axis(mesh, i);
			center_y_axis(mesh, i);
			center_z_axis(mesh, i);
			i += 8;
		}
		mesh->axis[1] = vec3f_mul_scalar(vec3f_add(mesh->axis[1], \
												mesh->axis[0]), 0.5f);
		return (true);
	}
	return (error_bool("[ERROR get_center_axis]\t" \
	"NULL mesh pointer!\n"));
}
