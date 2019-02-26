/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_line_process_normal.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:38:44 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/26 15:54:05 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool		create_normal_array(t_mesh *mesh)
{
	if (mesh)
	{
		if (!(mesh->normal = ft_memalloc(sizeof(float) \
											* 3 * mesh->n_normal[0])))
			return ((error_bool("[ERROR create_normal_array()]\t" \
			"Mesh normal array memory allocation failed!\n")));
		return (true);
	}
	return ((error_bool("[ERROR create_normal_array()]\t" \
	"NULL mesh pointer!\n")));
}

bool			mesh_line_process_normal(t_mesh *mesh, char *str)
{
	size_t		i[2];

	if (mesh && str)
	{
		if (!mesh->normal && mesh->n_normal > 0)
			if (!create_normal_array(mesh))
				return (error_bool("[ERROR mesh_line_process_normal()]\t" \
				"Mesh normal array creation failed!\n"));
		i[0] = (++mesh->n_normal[1] - 1) * 3;
		i[1] = sscanf(str, "vn %f %f %f\n", &mesh->normal[i[0]], \
					&mesh->normal[i[0] + 1], &mesh->normal[i[0]] + 2);
		if (i[1] != 3)
			return (error_bool("[ERROR mesh_line_process_normal()]\t" \
			"Missing value in vertex normal definition line!\n"));
		return (true);
	}
	return ((error_bool("[ERROR mesh_line_process_normal()]\t" \
	"NULL mesh or line pointer!\n")));
}
