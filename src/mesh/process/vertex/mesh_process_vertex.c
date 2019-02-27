/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_process_vertex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:58:21 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/27 18:18:12 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool		create_v_array(t_mesh *mesh)
{
	if (mesh)
	{
		if (!(mesh->vertex = ft_memalloc(sizeof(float) \
										* 8 * mesh->n_vertex[0])))
			return ((error_bool("[ERROR create_v_array]\t" \
			"Mesh vertex array memory allocation failed!\n")));
		return (true);
	}
	return ((error_bool("[ERROR create_v_array]\t" \
	"NULL mesh pointer!\n")));
}

static bool		check_vertex_data(t_mesh *mesh, const int index, const int ret)
{
	if (mesh)
	{
		// NEEDS TO BE FINISHEDD!!!!!!
		if (ret == 8)
			return (true);
		else if (ret == 3)	// 3 comp without color
		{
			mesh->vertex[index + 3] = 1.0f;
			mesh->vertex[index + 4] = 0.42f;
			mesh->vertex[index + 5] = 0.0f;
			mesh->vertex[index + 6] = 0.70f;
			mesh->vertex[index + 7] = 1.0f;
		}
		else if (ret == 4)	// 4 comp without color
		{
			mesh->vertex[index + 4] = 0.42f;
			mesh->vertex[index + 5] = 0.0f;
			mesh->vertex[index + 6] = 0.70f;
			mesh->vertex[index + 7] = 1.0f;
		}
		else if (ret == 7)	// 4 comp without color
			mesh->vertex[index + 7] = 1.0f;
		else
			return ((error_bool("[ERROR check_vertex_data]\t" \
			"Vertex line format is incorrect\n" \
			"It needs to be X Y Z W R G B A\n" \
			"XYZ are mandatory, if you put color you need to specify at least the RGB!\n")));
		return (true);
	}
	return ((error_bool("[ERROR check_vertex_data]\t" \
	"NULL mesh pointer!\n")));
}


bool	mesh_process_vertex(t_mesh *mesh, char *str)
{
	int			i[2];

	if (mesh && str)
	{
		if (!mesh->vertex && mesh->n_vertex[0] > 0)
			if (!create_v_array(mesh))
				return (error_bool("[ERROR mesh_process_vertex]\t" \
				"Mesh vertex array creation failed!\n"));
		i[0] = (++mesh->n_vertex[1] - 1) * 8;
		i[1] = sscanf(str, "v %f %f %f %f %f %f %f %f\n",
					&mesh->vertex[i[0]], &mesh->vertex[i[0] + 1], \
					&mesh->vertex[i[0] + 2], &mesh->vertex[i[0] + 3], \
					&mesh->vertex[i[0] + 4], &mesh->vertex[i[0] + 5], \
					&mesh->vertex[i[0] + 6], &mesh->vertex[i[0] + 7]);
		if (i[1] < 3)
			return (!scop_log_err("[ERROR mesh_process_vertex]\t" \
				"Missing value in vertex definition line!\n", str));
		if (!(check_vertex_data(mesh, i[0], i[1])))
			return (error_bool("[ERROR mesh_process_vertex]\t" \
				"Missing values in vertex definition line!\n"));
		return (true);
	}
	return ((error_bool("[ERROR mesh_process_vertex]\t" \
	"NULL mesh or string pointer!\n")));
}
