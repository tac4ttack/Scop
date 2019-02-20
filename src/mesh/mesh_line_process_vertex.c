/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_line_process_vertex.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:38:27 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/20 17:13:32 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool		create_vertex_array(t_mesh *mesh)
{
	if (mesh)
	{
		if (!(mesh->vertex = ft_memalloc(sizeof(float) * 4)))
			return (error_bool("[ERROR create_vertex_array()]\t" \
			"Mesh vertex array memory allocation failed"));
		mesh->n_vertex = 1;
		mesh->vertex[3] = 1.0f;
		return (true);
	}
	return (false);
}

static bool		extend_vertex_array(t_mesh *src)
{
	float		*new;

	if (src)
	{
		if (!(new = ft_memalloc(sizeof(float) * ((src->n_vertex + 1) * 4))))
			return (error_bool("[ERROR extend_vertex_array()]\t" \
			"New mesh vertex array memory allocation failed"));
		if (!(new = ft_memcpy(new, src->vertex, \
							(sizeof(float) * (src->n_vertex) * 4))))
			return (error_bool("[ERROR extend_vertex_array()]\t" \
			"Old mesh vertex array data copy to new array failed"));
		src->n_vertex++;
		free(src->vertex);
		src->vertex = new;
		src->vertex[((src->n_vertex - 1) * 4) + 3] = 1.0f;
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
		if (!mesh->vertex)
		{
			if (!create_vertex_array(mesh))
				return (error_bool("[ERROR mesh_line_process_vertex()]\t" \
				"Mesh vertex array creation failed"));
		}
		else
		{
			if (!extend_vertex_array(mesh))
				return (error_bool("[ERROR mesh_line_process_vertex()]\t" \
				"Mesh vertex array extension failed"));
		}
		index = (mesh->n_vertex - 1) * 4;
		ret = sscanf(str, "v %f %f %f %f\n",
					&mesh->vertex[index], &mesh->vertex[index + 1], \
					&mesh->vertex[index + 2], &mesh->vertex[index + 3]);
		(ret == 3 ? mesh->vertex[index + 3] = 1.0f : 0);
		return (0);
	}
	return (-1);
}
