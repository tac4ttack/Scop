/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_prepack_vao_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:33:55 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/24 16:42:57 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	prepack_vao_data_push_pos_hue(t_scop *env, size_t i)
{
	if (env && env->mesh)
	{
		if (env->mesh->vertex)
		{
			env->prepack_vao[(i * VAOLEN)] = env->mesh->vertex[(i * 8)];
			env->prepack_vao[(i * VAOLEN) + 1] = env->mesh->vertex[(i * 8) + 1];
			env->prepack_vao[(i * VAOLEN) + 2] = env->mesh->vertex[(i * 8) + 2];
			env->prepack_vao[(i * VAOLEN) + 3] = env->mesh->vertex[(i * 8) + 3];
			env->prepack_vao[(i * VAOLEN) + 4] = env->mesh->vertex[(i * 8) + 4];
			env->prepack_vao[(i * VAOLEN) + 5] = env->mesh->vertex[(i * 8) + 5];
			env->prepack_vao[(i * VAOLEN) + 6] = env->mesh->vertex[(i * 8) + 6];
			env->prepack_vao[(i * VAOLEN) + 7] = env->mesh->vertex[(i * 8) + 7];
		}
	}
}

static bool	prepack_push_vertex_data(t_scop *env, int v, int vt, int vn)
{
	if (env && env->mesh)
	{
		v *= VAOLEN;
		vt *= 3;
		vn *= 3;
		if (env->mesh->texture && vt >= 0 && (size_t)vt < env->mesh->n_texture[0] * 3)
		{
			env->prepack_vao[v + 8] = env->mesh->texture[vt];
			env->prepack_vao[v + 9] = env->mesh->texture[vt + 1];
			env->prepack_vao[v + 10] = env->mesh->texture[vt + 2];
		}
		if (env->mesh->normal && vn >= 0 && (size_t)vn < env->mesh->n_normal[0] * 3)
		{
			env->prepack_vao[v + 11] = env->mesh->normal[vn];
			env->prepack_vao[v + 12] = env->mesh->normal[vn + 1];
			env->prepack_vao[v + 13] = env->mesh->normal[vn + 2];
		}
		// else
		// {
			/*	ok gros kiproko ici, je pensais que j'allais devoir calculer une
				normal pour chaque vertex alors qu'en fait c'est pour chaque
				triangle.
				Donc va falloir changer la taille du VBO de 17 à 14?
				Et aussi trouver où stocker les normales pour chaque face?
		
				new edit: en fait j'y étais presque. on va devoir duppliquer
				les vertices (faces * 3) pour qu'ils aient chacun leur normal
				qu'elle soit dans le fichier ou à calculer par moi meme
			*/
					
			/*
			Begin Function CalculateSurfaceNormal (Input Triangle) Returns Vector

			Set Vector U to (Triangle.p2 minus Triangle.p1)
			Set Vector V to (Triangle.p3 minus Triangle.p1)

			Set Normal.x to (multiply U.y by V.z) minus (multiply U.z by V.y)
			Set Normal.y to (multiply U.z by V.x) minus (multiply U.x by V.z)
			Set Normal.z to (multiply U.x by V.y) minus (multiply U.y by V.x)

			Returning Normal

			End Function
			 */

			
			// ft_putendl("should be computing triangle normal manually");
		// }
		return (true);
	}
	return (error_bool("[ERROR prepack_push_vertex_data]\t" \
	"NULL Scop or mesh pointer!\n"));
}

static bool	mesh_preprack_push_face_data(t_scop *env, size_t pos)
{
	int i[10];

	if (env && env->mesh)
	{
		i[0] = 0;
		while (i[0] < 9)
		{
			i[i[0] + 1] = env->mesh->face[pos + i[0]];
			i[0]++;
		}
		if (!(prepack_push_vertex_data(env, i[1], i[2], i[3])))
			return (error_bool("[ERROR mesh_prepack_push_face_data]\t" \
			"Face\'s first vertex data push failed!\n"));
		if (!(prepack_push_vertex_data(env, i[4], i[5], i[6])))
			return (error_bool("[ERROR mesh_prepack_push_face_data]\t" \
			"Face\'s second vertex data push failed!\n"));
		if (!(prepack_push_vertex_data(env, i[7], i[8], i[9])))
			return (error_bool("[ERROR mesh_prepack_push_face_data]\t" \
			"Face\'s third vertex data push failed!\n"));
		return (true);
	}
	return (error_bool("[ERROR mesh_prepack_push_face_data]\t" \
	"NULL Scop or mesh pointer!\n"));
}

bool		mesh_prepack_vao_data(t_scop *env)
{
	size_t	i;

	if (env && env->mesh && !(i = 0))
	{
		scop_log("Packing data for a big VAO...\n", NULL);
		if (!(env->prepack_vao = ft_memalloc(sizeof(GLfloat) \
										* env->mesh->n_vertex[0] * VAOLEN)))
			return (error_bool("[ERROR mesh_pack_vao_data]\t" \
			"Could not allocate memory for the VAO data packing!\n"));
		while (i < env->mesh->n_vertex[0])
			prepack_vao_data_push_pos_hue(env, i++);
		if (env->mesh->face && !(i = 0))
			while (i < env->mesh->n_face[0] * 9)
			{
				if (!(mesh_preprack_push_face_data(env, i)))
					return (error_bool("[ERROR mesh_pack_vao_data]\t" \
					"Error while filling VAO prepack with faces data!\n"));
				i += 9;
			}
		scop_log("Successfully packed VAO data!\n", NULL);
		return (true);
	}
	return (error_bool("[ERROR mesh_pack_vao_data]\tNULL Scop pointer!\n"));
}
