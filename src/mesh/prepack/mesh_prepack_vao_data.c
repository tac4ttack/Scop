/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_prepack_vao_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:33:55 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/06 18:34:57 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	prepack_vao_data_push_pos_hue(t_mesh *mesh, size_t index)
{
	if (mesh)
	{
		if (mesh->vertex)
		{
			mesh->prepack_vao[(index * 17)] = mesh->vertex[(index * 8)];
			mesh->prepack_vao[(index * 17) + 1] = mesh->vertex[(index * 8) + 1];
			mesh->prepack_vao[(index * 17) + 2] = mesh->vertex[(index * 8) + 2];
			mesh->prepack_vao[(index * 17) + 3] = mesh->vertex[(index * 8) + 3];
			mesh->prepack_vao[(index * 17) + 4] = mesh->vertex[(index * 8) + 4];
			mesh->prepack_vao[(index * 17) + 5] = mesh->vertex[(index * 8) + 5];
			mesh->prepack_vao[(index * 17) + 6] = mesh->vertex[(index * 8) + 6];
			mesh->prepack_vao[(index * 17) + 7] = mesh->vertex[(index * 8) + 7];
		}
	}
}

static bool	prepack_push_vertex_data(t_mesh *mesh, int v, int vt, int vn)
{
	if (mesh)
	{
		if (mesh->texture && vt > 0 && (size_t)vt < mesh->n_texture[0])
		{
			mesh->prepack_vao[v + 8] = mesh->texture[vt];
			mesh->prepack_vao[v + 9] = mesh->texture[vt + 1];
			mesh->prepack_vao[v + 10] = mesh->texture[vt + 2];
		}
		if (mesh->normal && vn > 0 && (size_t)vn < mesh->n_normal[0])
		{
			mesh->prepack_vao[v + 11] = mesh->normal[vn];
			mesh->prepack_vao[v + 12] = mesh->normal[vn + 1];
			mesh->prepack_vao[v + 13] = mesh->normal[vn + 2];
		}
		return (true);
	}
	return (error_bool("[ERROR prepack_push_vertex_data]\t" \
	"NULL mesh pointer!\n"));
}

static bool	mesh_preprack_push_face_data(t_mesh *mesh, size_t pos)
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

		fprintf(stdout, "\nDEBUG push face data\n" \
		"#0 -> %d\n\n#1 -> %d\n#2 -> %d\n#3 -> %d\n\n#4 -> %d\n#5 -> %d\n#6 "\
		"-> %d\n\n#7 -> %d\n#8 -> %d\n#9 -> %d\n",\
		i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7], i[8], i[9]);

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

bool		mesh_prepack_vao_data(t_mesh *mesh)
{
	size_t	i;

	if (mesh && !(i = 0))
	{
		scop_log("Packing data for a big VAO...\n", NULL);
		if (!(mesh->prepack_vao = ft_memalloc(sizeof(GLfloat) \
											* mesh->n_vertex[0] * 17)))
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
