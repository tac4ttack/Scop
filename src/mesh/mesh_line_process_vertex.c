/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_line_process_vertex.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:38:27 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/23 19:24:43 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool		create_vertex_array(t_mesh *mesh)
{
	if (mesh)
	{
		if (!(mesh->vertex = ft_memalloc(sizeof(float) * 4 * *mesh->n_vertex)))
			return (error_bool("[ERROR create_vertex_array()]\t" \
			"Mesh vertex array memory allocation failed"));
		return (true);
	}
	return (false);
}

bool			mesh_line_process_vertex(t_mesh *mesh, char *str)
{
	int			index;
	int			ret;

	if (mesh && str)
	{
		if (!mesh->vertex && mesh->n_vertex[0] > 0)
		{
			if (!create_vertex_array(mesh))
				return (error_bool("[ERROR mesh_line_process_vertex()]\t" \
				"Mesh vertex array creation failed"));
		}
		index = (++mesh->n_vertex[1] - 1) * 4;
		ret = sscanf(str, "v %f %f %f %f\n",
					&mesh->vertex[index], &mesh->vertex[index + 1], \
					&mesh->vertex[index + 2], &mesh->vertex[index + 3]);
		if (ret < 3)
			return (!scop_log_err("[ERROR mesh_line_process_vertex()]\t" \
				"Missing value in vertex definition line\n", str));
		(ret == 3 ? mesh->vertex[index + 3] = 1.0f : 0);
		return (true);
	}
	return (false);
}
