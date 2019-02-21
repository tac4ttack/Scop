/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_file_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:15:07 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/21 18:25:49 by fmessina         ###   ########.fr       */
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

static void *line_processing_error(t_mesh **trash, char **split)
{
	if (trash)
		ft_memdel((void**)&(*trash));
	if (split)
		split_destroy(split);
	return (error("[ERROR mesh_file_process()]\t" \
				"Mesh line processing failed"));
}

void	mesh_clean(t_mesh *mesh)
{
	if (mesh)
	{
		(mesh->object ? ft_memdel((void**)&mesh->object) : 0);
		(mesh->group ? ft_memdel((void**)&mesh->group) : 0);
		(mesh->mtllib ? ft_memdel((void**)&mesh->mtllib) : 0);
		(mesh->usemtl ? ft_memdel((void**)&mesh->usemtl) : 0);
		(mesh->vertex ? ft_memdel((void**)&mesh->vertex) : 0);
		(mesh->face ? ft_memdel((void**)&mesh->face) : 0);
		(mesh->normal ? ft_memdel((void**)&mesh->normal) : 0);
		(mesh->texture ? ft_memdel((void**)&mesh->texture) : 0);
		(mesh->space ? ft_memdel((void**)&mesh->space) : 0);
	}
}


t_mesh *mesh_file_process(t_scop *env)
{
	t_mesh	*mesh;
	char	**split;

	mesh = NULL;
	if (env && env->mesh_data)
	{
		scop_log("\nProcessing mesh...\n");
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
			return (line_processing_error(&mesh, split));
		(DEBUG_SCOP ? mesh_print_data(mesh) : 0);
		split_destroy(split);
		scop_log("Finished mesh processing with success!\n");
		return (mesh);
	}
	return (NULL);
}
