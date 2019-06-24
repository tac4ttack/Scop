/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _mesh_file_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:15:07 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/24 11:23:00 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

 static t_obj	*create_mesh(t_obj *target)
{
	if (!(target = ft_memalloc(sizeof(t_obj))))
		return (error("[ERROR create_mesh]\t" \
		"Mesh memory allocation failed!\n"));
	target->vertex = NULL;
	target->face = NULL;
	return (target);
}

static void 	*mesh_file_processing_error(t_obj *mesh, char **split, char *msg)
{
	if (mesh)
		mesh_clean(mesh);
	if (split)
		split_destroy(split);
	return (error(msg));
}

t_obj			*mesh_file_process(t_scop *env)
{
	t_obj		*mesh;
	char		**split;

	mesh = NULL;
	if (env && env->mesh_data)
	{
		scop_log("\nProcessing mesh...\n");
		if (!(env->mesh_data = ft_strtrim_free(env->mesh_data)))
			return (error("[ERROR mesh_file_process]\t" \
							"Mesh data trimming failed!\n"));
		if (!(split = ft_strsplit(env->mesh_data, '\n')))
			return (error("[ERROR mesh_file_process]\t" \
							"Mesh data split failed!\n"));
		if (!(mesh = create_mesh(mesh)))
			return (mesh_file_processing_error(mesh, split, \
			"[ERROR mesh_file_process]\tMesh data creation failed!\n"));
		if (!mesh_line_process(mesh, split))
			return (mesh_file_processing_error(mesh, split, \
			"[ERROR mesh_file_process]\tMesh line processing failed!\n"));
		split_destroy(split);
		scop_log("Finished mesh processing with success!\n");
		return (mesh);
	}
	return (NULL);
}
