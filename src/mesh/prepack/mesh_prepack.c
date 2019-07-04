/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_prepack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:07:32 by fmessina          #+#    #+#             */
/*   Updated: 2019/07/04 14:21:59 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool	mesh_prepack_memalloc(t_scop *env)
{
	if (env)
	{
		if (!(mesh_prepack_get_center_axis(env->mesh)) \
			|| !mesh_prepack_center_vertices(env->mesh))
			return (error_bool("[ERROR mesh_prepack]\t" \
			"Failed to recenter mesh and compute its main axis!\n"));
		if (env->mesh->face && env->mesh->n_face[0] > 0)
		{
			if (!(env->prepack_ebo = ft_memalloc(sizeof(GLint) \
												* env->mesh->n_face[0] * 3)))
				return (error_bool("[ERROR mesh_prepack]\t" \
				"Could not allocate memory for the EBO data buffer!\n"));
			if (!(env->prepack_vao = ft_memalloc(sizeof(GLfloat) \
										* env->mesh->n_face[0] * 3 * VAOLEN)))
				return (error_bool("[ERROR mesh_prepack]\t" \
				"Could not allocate memory for the VAO data buffer!\n"));
		}
		else
		{
			if (!(env->prepack_ebo = ft_memalloc(sizeof(GLint) \
												* env->mesh->n_vertex[0])))
				return (error_bool("[ERROR mesh_prepack]\t" \
				"Could not allocate memory for the EBO data buffer!\n"));
			if (!(env->prepack_vao = ft_memalloc(sizeof(GLfloat) \
										* env->mesh->n_vertex[0] * VAOLEN)))
				return (error_bool("[ERROR mesh_prepack]\t" \
				"Could not allocate memory for the VAO data buffer!\n"));
		}
		if (!(mesh_prepack_ebo_check_indexes(env->mesh)))
			return (error_bool("[ERROR mesh_prepack]\t" \
			"Failed reverting negative indexes in face elements!\n"));
		return (true);
	}
	return (error_bool("[ERROR mesh_prepack_memalloc]\tNULL mesh pointer!\n"));
}

static void	mesh_prepack_texture_normals(t_scop *env, size_t i, int face[3])
{
	if (env)
	{
		if (env->mesh->texture)
		{
			env->prepack_vao[(i * VAOLEN) + 8] = \
				env->mesh->texture[(face[1] * 3) + 0];
			env->prepack_vao[(i * VAOLEN) + 9] = \
				env->mesh->texture[(face[1] * 3) + 1];
			env->prepack_vao[(i * VAOLEN) + 10] = \
				env->mesh->texture[(face[1] * 3) + 2];
		}
		if (env->mesh->normal)
		{
			env->prepack_vao[(i * VAOLEN) + 11] = \
				env->mesh->normal[(face[2] * 3) + 0];
			env->prepack_vao[(i * VAOLEN) + 12] = \
				env->mesh->normal[(face[2] * 3) + 1];
			env->prepack_vao[(i * VAOLEN) + 13] = \
				env->mesh->normal[(face[2] * 3) + 2];
		}
	}
}

static void	mesh_prepack_vertex_pos_hue(t_scop *env, size_t i, int face[3])
{
	int		j;

	if (env && !(j = 0))
	{
		env->prepack_vao[(i * VAOLEN) + 0] = \
			env->mesh->vertex[(face[0] * 8) + 0];
		env->prepack_vao[(i * VAOLEN) + 1] = \
			env->mesh->vertex[(face[0] * 8) + 1];
		env->prepack_vao[(i * VAOLEN) + 2] = \
			env->mesh->vertex[(face[0] * 8) + 2];
		env->prepack_vao[(i * VAOLEN) + 3] = \
			env->mesh->vertex[(face[0] * 8) + 3];
		env->prepack_vao[(i * VAOLEN) + 4] = \
			env->mesh->vertex[(face[0] * 8) + 4];
		env->prepack_vao[(i * VAOLEN) + 5] = \
			env->mesh->vertex[(face[0] * 8) + 5];
		env->prepack_vao[(i * VAOLEN) + 6] = \
			env->mesh->vertex[(face[0] * 8) + 6];
		env->prepack_vao[(i * VAOLEN) + 7] = \
			env->mesh->vertex[(face[0] * 8) + 7];
		// while (j < 8)
		// {
		// 	env->prepack_vao[(i * VAOLEN) + j] = \
		// 								env->mesh->vertex[(face[0] * 8) + j];
		// 	j++;
		// }
	}
}

bool		mesh_prepack(t_scop *env)
{
	size_t	i;
	int		face[3];

	if (env)
	{
		if (!(mesh_prepack_memalloc(env)))
			return (error_bool("[ERROR mesh_prepack]\t" \
			"Could not allocate memory for EBO and VAO!\n"));
		if (env->mesh && !(i = 0))
		{
			if (i < env->mesh->n_face[0] * 3)
			{
				while (i < env->mesh->n_face[0] * 3)
				{
					face[0] = env->mesh->face[(i * 3)];
					face[1] = env->mesh->face[(i * 3) + 1];
					face[2] = env->mesh->face[(i * 3) + 2];
					env->prepack_ebo[i] = i;
					mesh_prepack_vertex_pos_hue(env, i, face);
					mesh_prepack_texture_normals(env, i, face);
					i++;
				}
			}
			else
			{
				while (i < env->mesh->n_vertex[1])
				{
					env->prepack_vao[(i * VAOLEN) + 0] = env->mesh->vertex[(i * 8) + 0];
					env->prepack_vao[(i * VAOLEN) + 1] = env->mesh->vertex[(i * 8) + 1];
					env->prepack_vao[(i * VAOLEN) + 2] = env->mesh->vertex[(i * 8) + 2];
					env->prepack_vao[(i * VAOLEN) + 3] = env->mesh->vertex[(i * 8) + 3];
					env->prepack_vao[(i * VAOLEN) + 4] = env->mesh->vertex[(i * 8) + 4];
					env->prepack_vao[(i * VAOLEN) + 5] = env->mesh->vertex[(i * 8) + 5];
					env->prepack_vao[(i * VAOLEN) + 6] = env->mesh->vertex[(i * 8) + 6];
					env->prepack_vao[(i * VAOLEN) + 7] = env->mesh->vertex[(i * 8) + 7];
					i++;
				}
			}
			return (true);
		}
	}
	return (error_bool("[ERROR mesh_prepack]\tNULL env pointer!\n"));
}
