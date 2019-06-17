/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_process_normal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:38:44 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/10 18:49:53 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool		create_vn_array(t_mesh *mesh)
{
	if (mesh)
	{
		if (!(mesh->normal = ft_memalloc(sizeof(float) \
											* 3 * mesh->n_normal[0])))
			return (error_bool("[ERROR create_vn_array]\t" \
			"Mesh normal array memory allocation failed!\n"));
		return (true);
	}
	return (error_bool("[ERROR create_vn_array]\t" \
	"NULL mesh pointer!\n"));
}

static bool		normalize_vertex_normal(t_mesh *mesh, const size_t index)
{
	float	vec[4];

	if (mesh)
	{
		vec[0] = mesh->normal[index];
		vec[1] = mesh->normal[index + 1];
		vec[2] = mesh->normal[index + 2];
		vec[3] = sqrt((vec[0] * vec[0]) \
					+ (vec[1] * vec[1]) \
					+ (vec[2] * vec[2]));
		mesh->normal[index] = vec[0] / vec[3];
		mesh->normal[index + 1] = vec[1] / vec[3];
		mesh->normal[index + 2] = vec[2] / vec[3];
		return (true);
	}
	return (error_bool("[ERROR normalize_vertex_normal]\t" \
	"NULL mesh pointer!\n"));
}

// est-ce toujours d'actualité avec le mesh prepack?
// WIP si pas de normal alors la calculer?????
bool			mesh_process_normal(t_mesh *mesh, char *str)
{
	size_t		i[2];

	if (mesh && str)
	{
		if (!mesh->normal && mesh->n_normal > 0)
			if (!create_vn_array(mesh))
				return (error_bool("[ERROR mesh_process_normal]\t" \
				"Mesh normal array creation failed!\n"));
		i[0] = (++mesh->n_normal[1] - 1) * 3;
		i[1] = sscanf(str, "vn %f %f %f\n", &mesh->normal[i[0]], \
					&mesh->normal[i[0] + 1], &mesh->normal[i[0]] + 2);
		if (i[1] != 3)
			return (error_bool("[ERROR mesh_process_normal]\t" \
			"Wrong format in vertex normal definition line!\n"));
		if (!normalize_vertex_normal(mesh, i[0]))
			return (error_bool("[ERROR mesh_process_normal]\t" \
			"Could not normalize vertex normal!\n"));
		return (true);
	}
	return (error_bool("[ERROR mesh_process_normal]\t" \
	"NULL mesh or string pointer!\n"));
}
