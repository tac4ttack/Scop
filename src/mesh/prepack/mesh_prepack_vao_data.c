/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_prepack_vao_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:33:55 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/24 11:22:59 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	prepack_vao_data_push_pos_hue(t_obj *mesh, size_t i)
{
	if (mesh)
	{
		if (mesh->vertex)
		{
			mesh->prepack_vao[(i * VAOSIZE)] = mesh->vertex[(i * 8)];
			mesh->prepack_vao[(i * VAOSIZE) + 1] = mesh->vertex[(i * 8) + 1];
			mesh->prepack_vao[(i * VAOSIZE) + 2] = mesh->vertex[(i * 8) + 2];
			mesh->prepack_vao[(i * VAOSIZE) + 3] = mesh->vertex[(i * 8) + 3];
			mesh->prepack_vao[(i * VAOSIZE) + 4] = mesh->vertex[(i * 8) + 4];
			mesh->prepack_vao[(i * VAOSIZE) + 5] = mesh->vertex[(i * 8) + 5];
			mesh->prepack_vao[(i * VAOSIZE) + 6] = mesh->vertex[(i * 8) + 6];
			mesh->prepack_vao[(i * VAOSIZE) + 7] = mesh->vertex[(i * 8) + 7];
		}
	}
}

static bool	prepack_push_vertex_data(t_obj *mesh, int v, int vt, int vn)
{
	if (mesh)
	{
		// fprintf(stdout, "\ndebug push vertex\nv = %d | vt = %d | vn = %d\n", v, vt, vn);
		v *= 14;
		vt *= 3;
		vn *= 3;
		if (mesh->texture && vt >= 0 && (size_t)vt < mesh->n_texture[0] * 3)
		{
			mesh->prepack_vao[v + 8] = mesh->texture[vt];
			mesh->prepack_vao[v + 9] = mesh->texture[vt + 1];
			mesh->prepack_vao[v + 10] = mesh->texture[vt + 2];
		}
		if (mesh->normal && vn >= 0 && (size_t)vn < mesh->n_normal[0] * 3)
		{
			// ft_putendl("using obj file vertex normal data");
			
			
			mesh->prepack_vao[v + 11] = mesh->normal[vn];
			mesh->prepack_vao[v + 12] = mesh->normal[vn + 1];
			mesh->prepack_vao[v + 13] = mesh->normal[vn + 2];
		}
		else
		{
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
		}
		return (true);
	}
	return (error_bool("[ERROR prepack_push_vertex_data]\t" \
	"NULL mesh pointer!\n"));
}

static bool	mesh_preprack_push_face_data(t_obj *mesh, size_t pos)
{
	int i[10];

	if (mesh)
	{
		i[0] = 0;
		while (i[0] < 9)
		{
			i[i[0] + 1] = mesh->face[pos + i[0]];
			i[0]++;
		}
		if (!(prepack_push_vertex_data(mesh, i[1], i[2], i[3])))
			return (error_bool("[ERROR mesh_prepack_push_face_data]\t" \
			"First face\'s vertex data push failed!\n"));
		if (!(prepack_push_vertex_data(mesh, i[4], i[5], i[6])))
			return (error_bool("[ERROR mesh_prepack_push_face_data]\t" \
			"Second face\'s vertex data push failed!\n"));
		if (!(prepack_push_vertex_data(mesh, i[7], i[8], i[9])))
			return (error_bool("[ERROR mesh_prepack_push_face_data]\t" \
			"Third face\'s vertex data push failed!\n"));
		return (true);
	}
	return (error_bool("[ERROR mesh_prepack_push_face_data]\t" \
	"NULL mesh pointer!\n"));
}

bool		mesh_prepack_vao_data(t_obj *mesh)
{
	size_t	i;

	if (mesh && !(i = 0))
	{
		scop_log("Packing data for a big VAO...\n", NULL);
		if (!(mesh->prepack_vao = ft_memalloc(sizeof(GLfloat) \
											* mesh->n_vertex[0] * VAOSIZE)))
			return (error_bool("[ERROR mesh_pack_vao_data]\t" \
			"Could not allocate memory for the VAO data packing!\n"));
		while (i < mesh->n_vertex[0])
			prepack_vao_data_push_pos_hue(mesh, i++);
		if (mesh->face && !(i = 0))
			while (i < mesh->n_face[0] * 9)
			{
				if (!(mesh_preprack_push_face_data(mesh, i)))
					return (error_bool("[ERROR mesh_pack_vao_data]\t" \
					"Error while filling VAO prepack with faces data!\n"));
				i += 9;
			}
		scop_log("Successfully packed VAO data!\n", NULL);
		return (true);
	}
	return (error_bool("[ERROR mesh_pack_vao_data]\tNULL mesh pointer!\n"));
}
