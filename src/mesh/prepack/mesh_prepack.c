/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_prepack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:07:32 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/25 16:49:09 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool	mesh_prepack_ebo_check_indexes_vertex(t_obj *mesh, int i)
{
	if (mesh)
	{
		mesh->face[i] += (mesh->face[i] < 0 ? mesh->n_vertex[0] : -1);
		mesh->face[i + 3] += (mesh->face[i + 3] < 0 ? mesh->n_vertex[0] : -1);
		mesh->face[i + 6] += (mesh->face[i + 6] < 0 ? mesh->n_vertex[0] : -1);
		return (true);
	}
	return (error_bool("[ERROR mesh_prepack_ebo_check_indexes_vertex]\t" \
	"NULL mesh pointer!\n"));
}

static bool	mesh_prepack_ebo_check_indexes_texture(t_obj *mesh, int i)
{
	if (mesh)
	{
		mesh->face[i + 1] += (mesh->face[i + 1] < 0 ? mesh->n_texture[0] : -1);
		mesh->face[i + 4] += (mesh->face[i + 4] < 0 ? mesh->n_texture[0] : -1);
		mesh->face[i + 7] += (mesh->face[i + 7] < 0 ? mesh->n_texture[0] : -1);
		return (true);
	}
	return (error_bool("[ERROR mesh_prepack_ebo_check_indexes_texture]\t" \
	"NULL mesh pointer!\n"));
}

static bool	mesh_prepack_ebo_check_indexes_normal(t_obj *mesh, int i)
{
	if (mesh)
	{
		mesh->face[i + 2] += (mesh->face[i + 2] < 0 ? mesh->n_normal[0] : -1);
		mesh->face[i + 5] += (mesh->face[i + 5] < 0 ? mesh->n_normal[0] : -1);
		mesh->face[i + 8] += (mesh->face[i + 8] < 0 ? mesh->n_normal[0] : -1);
		return (true);
	}
	return (error_bool("[ERROR mesh_prepack_ebo_check_indexes_normal]\t" \
	"NULL mesh pointer!\n"));
}

static bool	mesh_prepack_ebo_check_indexes(t_obj *mesh)
{
	size_t	i;

	if (mesh && !(i = 0))
	{
		while (i < mesh->n_face[0] * 9)
		{
			if (!(mesh_prepack_ebo_check_indexes_vertex(mesh, i)))
				return (error_bool("[ERROR mesh_prepack_ebo_check_indexes]\t" \
				"Failed to check vertex index!\n"));
			if (!(mesh_prepack_ebo_check_indexes_texture(mesh, i)))
				return (error_bool("[ERROR mesh_prepack_ebo_check_indexes]\t" \
				"Failed to check texture coordinates index!\n"));
			if (!(mesh_prepack_ebo_check_indexes_normal(mesh, i)))
				return (error_bool("[ERROR mesh_prepack_ebo_check_indexes]\t" \
				"Failed to check vertex normal index!\n"));
			i += 9;
		}
		return (true);
	}
	return (error_bool("[ERROR mesh_prepack_ebo_check_indexes]\t" \
	"NULL mesh pointer!\n"));
}

bool	mesh_prepack(t_scop *env)
{
	size_t i;

	if (env && !(i = 0))
	{
		if (!(mesh_prepack_get_center_axis(env->mesh)) \
			|| !mesh_prepack_center_vertices(env->mesh))
			return (error_bool("[ERROR mesh_prepack]\t" \
			"Failed to recenter mesh and compute its main axis!\n"));

		if (env && env->mesh && !(i = 0))
		{
			scop_log("Packing data for a EBO...\n", NULL);

			// memalloc for the EBO
			if (!(env->prepack_ebo = ft_memalloc(sizeof(GLint) \
												* env->mesh->n_face[0] * 3)))
			return (error_bool("[ERROR mesh_prepack]\t" \
				"Could not allocate memory for the EBO data buffer!\n"));
			
			// memalloc for the VAO
			if (!(env->prepack_vao = ft_memalloc(sizeof(GLfloat) \
										* env->mesh->n_face[0] * 3 * VAOLEN)))
			return (error_bool("[ERROR mesh_prepack]\t" \
				"Could not allocate memory for the VAO data buffer!\n"));
			
			// checking faces definition indexes
			if (!(mesh_prepack_ebo_check_indexes(env->mesh)))
				return (error_bool("[ERROR mesh_prepack]\t" \
					"Failed reverting negative indexes in face elements!\n"));

			int face[3];
			i = 0;
			while (i < env->mesh->n_face[0] * 3)
			{
				face[0] = env->mesh->face[(i * 3)];
				face[1] = env->mesh->face[(i * 3) + 1];
				face[2] = env->mesh->face[(i * 3) + 2];
				
				env->prepack_ebo[i] = i;
				env->prepack_vao[(i * VAOLEN) + 0] = env->mesh->vertex[(face[0] * 8) + 0];
				env->prepack_vao[(i * VAOLEN) + 1] = env->mesh->vertex[(face[0] * 8) + 1];
				env->prepack_vao[(i * VAOLEN) + 2] = env->mesh->vertex[(face[0] * 8) + 2];
				env->prepack_vao[(i * VAOLEN) + 3] = env->mesh->vertex[(face[0] * 8) + 3];

				env->prepack_vao[(i * VAOLEN) + 4] = env->mesh->vertex[(face[0] * 8) + 4];
				env->prepack_vao[(i * VAOLEN) + 5] = env->mesh->vertex[(face[0] * 8) + 5];
				env->prepack_vao[(i * VAOLEN) + 6] = env->mesh->vertex[(face[0] * 8) + 6];
				env->prepack_vao[(i * VAOLEN) + 7] = env->mesh->vertex[(face[0] * 8) + 7];
				
				if (env->mesh->texture)
				{
					env->prepack_vao[(i * VAOLEN) + 8] = env->mesh->texture[(face[1] * 3) + 0];
					env->prepack_vao[(i * VAOLEN) + 9] = env->mesh->texture[(face[1] * 3) + 1];
					env->prepack_vao[(i * VAOLEN) + 10] = env->mesh->texture[(face[1] * 3) + 2];
				}
				
				if (env->mesh->normal)
				{
					env->prepack_vao[(i * VAOLEN) + 11] = env->mesh->normal[(face[2] * 3) + 0];
					env->prepack_vao[(i * VAOLEN) + 12] = env->mesh->normal[(face[2] * 3) + 1];
					env->prepack_vao[(i * VAOLEN) + 13] = env->mesh->normal[(face[2] * 3) + 2];
				}
				i++;
			}
			return (true);
		}
	}
	return (error_bool("[ERROR mesh_prepack]\tNULL env pointer!\n"));
}
