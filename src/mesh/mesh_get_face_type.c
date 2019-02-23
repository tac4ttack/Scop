/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_get_face_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:28:16 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/23 17:18:38 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool		get_face_vertices_count(t_mesh *mesh, char *str, char **split)
{
	if (mesh && str)
	{
		if (!(split = ft_strsplit(str, ' ')))
			return (error_bool("[ERROR get_face_vertices_count()]\t" \
			"Mesh analysis failed could not split to count face vertices\n"));
		while (*split)
		{
			mesh->n_face[2]++;
			split++;
		}
		split -= mesh->n_face[2]--;
		if (mesh->n_face[2] < 3)
		{
			split_destroy(split);
			return (error_bool("[ERROR get_face_vertices_count()]\t" \
			"Mesh faces need at least 3 vertices!\n"));
		}
		split_destroy(split);
		return (true);
	}
	return (false);
}

static bool		get_face_mod(t_mesh *mesh, char *str, char **split)
{
	int			i;

	if (mesh && str)
	{
		if (!(split = ft_strsplit(str, ' ')))
			return (error_bool("[ERROR get_face_mod()]\tSplit failed!\n"));
		if (strstr(*(split + 1), "//"))
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
				return (error_bool("[ERROR get_face_mod()]\t" \
				"Invalid face, not a Vn | Vn/VTn | Vn/VTn/VNn | Vn//VNn\n"));
			}
			split_destroy(split);
		}
		return (true);
	}
	return (false);
}

bool			mesh_get_face_type(t_mesh *mesh, char *str)
{
	char		**split;

	split = NULL;
	if (mesh && str)
	{
		if (!(get_face_vertices_count(mesh, str, split)))
			return (error_bool("[ERROR get_face_type()]\t" \
			"Could not count how many vertices define a face\n"));
		if (!(get_face_mod(mesh, str, split)))
			return (error_bool("[ERROR get_face_type()]\t" \
			"Could not determine face format\n"));
		mesh->n_face[4] = (mesh->n_face[3] == 3 ? 2 : mesh->n_face[3] + 1);
		mesh->n_face[5] = mesh->n_face[2] * mesh->n_face[4];
		return (true);
	}
	return (false);
}
