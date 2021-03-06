/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_prepack_ebo_check_indices.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 18:17:14 by fmessina          #+#    #+#             */
/*   Updated: 2019/07/01 12:30:05 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool	mesh_prepack_ebo_check_indexes_vertex(t_obj *mesh, int i)
{
	if (mesh)
	{
		mesh->face[i] += (mesh->face[i] < 0 ? mesh->n_vertex[0] : -1);
		mesh->face[i + 3] += (mesh->face[i + 3] < 0 ? mesh->n_vertex[0] : -1);
		mesh->face[i + 6] += (mesh->face[i + 6] < 0 ? mesh->n_vertex[0] : -1);
		return (true);
	}
	return (error_bool("[ERROR mesh_prepack_ebo_check_indexes_vertex]\t" \
	"NULL mesh pointer!\n"));
}

static bool	mesh_prepack_ebo_check_indexes_texture(t_obj *mesh, int i)
{
	if (mesh)
	{
		mesh->face[i + 1] += (mesh->face[i + 1] < 0 ? mesh->n_texture[0] : -1);
		mesh->face[i + 4] += (mesh->face[i + 4] < 0 ? mesh->n_texture[0] : -1);
		mesh->face[i + 7] += (mesh->face[i + 7] < 0 ? mesh->n_texture[0] : -1);
		return (true);
	}
	return (error_bool("[ERROR mesh_prepack_ebo_check_indexes_texture]\t" \
	"NULL mesh pointer!\n"));
}

static bool	mesh_prepack_ebo_check_indexes_normal(t_obj *mesh, int i)
{
	if (mesh)
	{
		mesh->face[i + 2] += (mesh->face[i + 2] < 0 ? mesh->n_normal[0] : -1);
		mesh->face[i + 5] += (mesh->face[i + 5] < 0 ? mesh->n_normal[0] : -1);
		mesh->face[i + 8] += (mesh->face[i + 8] < 0 ? mesh->n_normal[0] : -1);
		return (true);
	}
	return (error_bool("[ERROR mesh_prepack_ebo_check_indexes_normal]\t" \
	"NULL mesh pointer!\n"));
}

bool		mesh_prepack_ebo_check_indexes(t_obj *mesh)
{
	size_t	i;

	if (mesh && !(i = 0))
	{
		while (i < mesh->n_face[0] * 9)
		{
			if (!(mesh_prepack_ebo_check_indexes_vertex(mesh, i)))
				return (error_bool("[ERROR mesh_prepack_ebo_check_indexes]\t" \
				"Failed to check vertex index!\n"));
			if (!(mesh_prepack_ebo_check_indexes_texture(mesh, i)))
				return (error_bool("[ERROR mesh_prepack_ebo_check_indexes]\t" \
				"Failed to check texture coordinates index!\n"));
			if (!(mesh_prepack_ebo_check_indexes_normal(mesh, i)))
				return (error_bool("[ERROR mesh_prepack_ebo_check_indexes]\t" \
				"Failed to check vertex normal index!\n"));
			i += 9;
		}
		return (true);
	}
	return (error_bool("[ERROR mesh_prepack_ebo_check_indexes]\t" \
	"NULL mesh pointer!\n"));
}
