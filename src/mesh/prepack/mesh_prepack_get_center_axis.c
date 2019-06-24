/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_prepack_get_center_axis.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 12:14:25 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/24 11:22:59 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		mesh_prepack_get_center_axis(t_obj *mesh)
{
	size_t	i;

	i = 0;
	mesh->axis[0] = vec3f(0.0f, 0.0f, 0.0f);
	mesh->axis[1] = vec3f(0.0f, 0.0f, 0.0f);
	if (mesh)
	{
		while (i < mesh->n_vertex[0] * 8)
		{
			mesh->vertex[i] < mesh->axis[0].x ? \
				mesh->axis[0].x = mesh->vertex[i] : 0;
			mesh->vertex[i] > mesh->axis[1].x ? \
				mesh->axis[1].x = mesh->vertex[i] : 0;
			mesh->vertex[i + 1] < mesh->axis[0].y ? \
				mesh->axis[0].y = mesh->vertex[i + 1] : 0;
			mesh->vertex[i + 1] > mesh->axis[1].y ? \
				mesh->axis[1].y = mesh->vertex[i + 1] : 0;
			mesh->vertex[i + 2] < mesh->axis[0].z ? \
				mesh->axis[0].z = mesh->vertex[i + 2] : 0;
			mesh->vertex[i + 2] > mesh->axis[1].z ? \
				mesh->axis[1].z = mesh->vertex[i + 2] : 0;
			i += 8;
		}
		mesh->axis[1] = vec3f_mul_scalar( \
						vec3f_add(mesh->axis[1], mesh->axis[0]), \
						0.5f);
		
		// DEBUG!
		vec3f_print(mesh->axis[1]);
		
		return (true);
	}
	return (error_bool("[ERROR mesh_prepack_get_center_axis]\t" \
	"NULL mesh pointer!\n"));
}
