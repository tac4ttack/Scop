/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_get_face_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:28:16 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/21 18:46:00 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool		get_face_vertices_count(t_mesh *mesh, char *str)
{
	char		**split;

	if (mesh && str)
	{
		if (!(split = ft_strsplit(str, ' ')))
			return (error_bool("[ERROR get_face_vertices_count()]\t" \
			"Mesh analysis failed could not split to count face vertices"));
		while (*split)
		{
			mesh->n_face_vertices++;
			split++;
		}
		split -= mesh->n_face_vertices--;
		if (mesh->n_face_vertices < 3)
			return (error_bool("[ERROR get_face_vertices_count()]\t" \
			"Mesh faces need at least 3 vertices!"));
		split_destroy(split);
		return (true);
	}
	return (false);
}

static bool		get_face_mod(t_mesh *mesh, char *str)
{
	char		**split;
	int			i;

	if (mesh && str)
	{
		if (!(split = ft_strsplit(str, ' ')))
			return (error_bool("[ERROR get_face_mod()]\t"
			"Could not count split to get first element"));
		if (strstr(*(split + 1), "//"))
			mesh->n_face_mod = 3;
		else
		{
			i = 0;
			while ((*(split + 1))[i])
				if ((*(split + 1))[i++] == '/')
					mesh->n_face_mod++;
			if (mesh->n_face_mod > 3)
				return (error_bool("[ERROR get_face_mod()]\t" \
				"Invalid face, not a Vn | Vn/VTn | Vn/VTn/VNn | Vn//VNn"));
		}
		split_destroy(split);
		return (true);
	}
	return (false);
}

bool			mesh_get_face_type(t_mesh *mesh, char *str)
{
	if (mesh && str)
	{
		if (!(get_face_vertices_count(mesh, str)))
			return (error_bool("[ERROR get_face_type()]\t" \
			"Could not count how many vertices define a face"));
		if (!(get_face_mod(mesh, str)))
			return (error_bool("[ERROR get_face_type()]\t" \
			"Could not determine face format"));
		mesh_print_face_type(mesh);
		return (true);
	}
	return (false);
}
