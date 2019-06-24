/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_prepack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:07:32 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/24 17:30:07 by fmessina         ###   ########.fr       */
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
	if (env)
	{
		// the centering should be ok and should be keepable
		if (!(mesh_prepack_get_center_axis(env->mesh)) \
			|| !mesh_prepack_center_vertices(env->mesh))
			return (error_bool("[ERROR mesh_prepack]\t" \
			"Failed to recenter mesh and compute its main axis!\n"));



		// EBO PROCESSING
		size_t i;
		if (env && env->mesh && !(i = 0))
		{
			scop_log("Packing data for a EBO...\n", NULL);

			// memalloc for the EBO
			if (!(env->prepack_ebo = ft_memalloc(sizeof(GLint) \
												* env->mesh->n_face[0] * 3)))
			return (error_bool("[ERROR mesh_prepack_ebo_data]\t" \
					"Could not allocate memory for the EBO data packing!\n"));
			// checking faces definition indexes
			if (!(mesh_prepack_ebo_check_indexes(env->mesh)))
				return (error_bool("[ERROR mesh_prepack_ebo_data]\t" \
					"Failed reverting negative indexes in face elements!\n"));


			// OK DONC LA TU CHECK TON CARNET TU DOIS FAIRE UN VRAI INDEXEUR ET BUILDER DE VBO
			// TU DOIS CHECK LES SOMMETS DEFINIS PAR LES FACES, VOIR S'IL EXISTE OU PAS, AGIR EN CONSEQUENCE
			// ET REMPLIR LE EBO COMME IL FAUT
			// CREER FUNCTION DE RECHERCE DE VERTEX IDENTIQUE DANS LE VAO?
		}

		
		// old shit
		// if (env->mesh->n_face[0] > 1)
		// 	if (!(mesh_prepack_ebo_data(env)))
		// 		return (error_bool("[ERROR mesh_prepack]\t" \
		// 		"Failed to pack EBO data!\n"));
		// if (!(mesh_prepack_vao_data(env)))
		// 	return (error_bool("[ERROR mesh_prepack]\t" \
		// 	"Failed to pack VAO data!\n"));
		
		return (true);
	}
	return (error_bool("[ERROR mesh_prepack]\tNULL env pointer!\n"));
}
