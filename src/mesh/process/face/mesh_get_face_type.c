/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_get_face_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:28:16 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/27 12:45:34 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool		get_face_vertices_count(t_mesh *mesh, char *str, char **split)
{
	if (mesh && str)
	{
		while (*split)
		{
			mesh->n_face[2]++;
			split++;
		}
		split -= mesh->n_face[2]--;
		if (mesh->n_face[2] < 3)
		{
			split_destroy(split);
			return (error_bool("[ERROR get_face_vertices_count]\t" \
			"Mesh faces need at least 3 vertices!\n"));
		}
		return (true);
	}
	return (false);
}

static bool		get_face_mod(t_mesh *mesh, char *str, char **split)
{
	int			i;

	if (mesh && str)
	{
		if (ft_strstr(*(split + 1), "//"))
			mesh->n_face[3] = 3;
		else
		{
			i = 0;
			while ((*(split + 1))[i])
				if ((*(split + 1))[i++] == '/')
					mesh->n_face[3]++;
			if (mesh->n_face[3] > 3)
			{
				split_destroy(split);
				return (error_bool("[ERROR get_face_mod]\t" \
				"Invalid face format!\n It must be of the following type:\n" \
				"[Vn] or [Vn/VTn] or [Vn/VTn/VNn] or [Vn//VNn]\n"));
			}
		}
		return (true);
	}
	return (false);
}

static bool		mesh_get_face_type_error(char **split, char *msg)
{
	if (split)
		split_destroy(split);
	if (msg)
		return (error_bool(msg));
	return (false);
}

bool			mesh_get_face_type(t_mesh *mesh, char *str)
{
	char		**split;

	if (mesh && str)
	{
		if (!(split = ft_strsplit(str, ' ')))
			return (error_bool("[ERROR mesh_get_face_type]\t" \
			"First face line split failed, aborting analysis!\n"));
		if (!(get_face_vertices_count(mesh, str, split)))
			return (mesh_get_face_type_error(split, "[ERROR mesh_get_face]" \
			"_type]\tCould not count how many vertices define a face!\n"));
		if (!(get_face_mod(mesh, str, split)))
			return (mesh_get_face_type_error(split, "[ERROR mesh_get_face_" \
			"type]\tCould not determine face format!\n"));
		mesh->n_face[4] = (mesh->n_face[3] == 3 ? 2 : mesh->n_face[3] + 1);
		mesh->n_face[5] = mesh->n_face[2] * mesh->n_face[4];
		split_destroy(split);
		return (true);
	}
	return (false);
}
