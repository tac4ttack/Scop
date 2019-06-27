/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_prepack_center_vertices.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 12:14:25 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/27 17:55:01 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		mesh_prepack_center_vertices(t_obj *mesh)
{
	size_t	i;
	float	angle;
	float	trans;

	i = 0;
	angle = 90.0f * (M_PI / 180);
	if (mesh)
	{
		while (i < mesh->n_vertex[0] * 8)
		{
			mesh->vertex[i] -= mesh->axis[1].x;
			mesh->vertex[i + 1] -= mesh->axis[1].y;
			mesh->vertex[i + 2] -= mesh->axis[1].z;
			trans = mesh->vertex[i] * cos(angle) \
					- mesh->vertex[i + 2] * sin(angle);
			mesh->vertex[i + 2] = mesh->vertex[i] * sin(angle) \
								+ mesh->vertex[i + 2] * cos(angle);
			mesh->vertex[i] = trans;
			i += 8;
		}
		mesh->axis[1] = vec3f(0.0f, 0.0f, 0.0f);
		return (true);
	}
	return (error_bool("[ERROR mesh_prepack_center_vertices]\t" \
	"NULL mesh pointer!\n"));
}
