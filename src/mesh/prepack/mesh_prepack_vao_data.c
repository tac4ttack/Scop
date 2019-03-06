/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_prepack_vao_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:33:55 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/06 15:50:28 by fmessina         ###   ########.fr       */
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

static void	prepack_vao_data_push_texture(t_mesh *mesh, size_t index)
{
	if (mesh)
	{
		if (mesh->texture)
		{
			mesh->prepack_vao[(index * 17) + 8] = mesh->face[(index * 3) + 1];
			mesh->prepack_vao[(index * 17) + 9] = mesh->face[(index * 3) + 4];
			mesh->prepack_vao[(index * 17) + 10] = mesh->face[(index * 3) + 7];
		}
	}

}

static void	prepack_vao_data_push_normal(t_mesh *mesh, size_t index)
{
	if (mesh)
	{
		if (mesh->normal)
		{
			mesh->prepack_vao[(index * 17) + 11] = mesh->face[(index * 3) + 2];
			mesh->prepack_vao[(index * 17) + 12] = mesh->face[(index * 3) + 5];
			mesh->prepack_vao[(index * 17) + 13] = mesh->face[(index * 3) + 8];
		}
	}
}

static void	prepack_vao_data_push_space(t_mesh *mesh, size_t index)
{
	if (mesh)
	{
		if (mesh->space)
		{
			mesh->prepack_vao[(index * 17) + 14] = mesh->space[(index * 3)];
			mesh->prepack_vao[(index * 17) + 15] = mesh->space[(index * 3) + 1];
			mesh->prepack_vao[(index * 17) + 16] = mesh->space[(index * 3) + 2];
		}
	}
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
		{
			prepack_vao_data_push_pos_hue(mesh, i);
			prepack_vao_data_push_texture(mesh, i);
			prepack_vao_data_push_normal(mesh, i);
			prepack_vao_data_push_space(mesh, i);
			i++;
		}
		scop_log("Successfully packed VAO data!\n", NULL);
		return (true);
	}
	return (error_bool("[ERROR mesh_pack_vao_data]\tNULL mesh pointer!\n"));
}
