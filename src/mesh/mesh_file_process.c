/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_file_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:15:07 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/19 19:17:59 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static t_mesh *create_mesh(t_mesh *target)
{
	if (!(target = ft_memalloc(sizeof(t_mesh))))
		return (error("[ERROR create_mesh()]\t" \
						"Mesh memory allocation failed"));
	target->vertex = NULL;
	target->face = NULL;
	return (target);
}

t_mesh *mesh_file_process(t_scop *env)
{
	t_mesh	*mesh;
	char	**split;

	mesh = NULL;
	if (env && env->mesh_data)
	{
		if (!(env->mesh_data = ft_strtrim_free(env->mesh_data)))
			return (error("[ERROR mesh_file_process()]\t" \
							"Mesh data trimming failed"));
		if (!(split = ft_strsplit(env->mesh_data, '\n')))
			return (error("[ERROR mesh_file_process()]\t" \
							"Mesh data split failed"));
		if (!(mesh = create_mesh(mesh)))
			return (error("[ERROR mesh_file_process()]\t" \
							"Mesh data creation failed"));
		if (!mesh_line_process(mesh, split))
			return (error("[ERROR mesh_file_process()]\t" \
							"Mesh line processing failed"));

		// (DEBUG_SCOP ? mesh_print_data(mesh) : 0);
		mesh_print_data(mesh);

		split_destroy(split);
		return (mesh);
	}
	return (NULL);
}
