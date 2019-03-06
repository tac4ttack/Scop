/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_pack_vao_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:33:55 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/06 13:53:42 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	mesh_pack_vao_data_push_pos_hue(t_mesh *mesh, size_t index)
{
	if (mesh)
	{
		if (mesh->vertex)
		{
			mesh->final_vao[(index * 17)] = mesh->vertex[(index * 8)];
			mesh->final_vao[(index * 17) + 1] = mesh->vertex[(index * 8) + 1];
			mesh->final_vao[(index * 17) + 2] = mesh->vertex[(index * 8) + 2];
			mesh->final_vao[(index * 17) + 3] = mesh->vertex[(index * 8) + 3];
			mesh->final_vao[(index * 17) + 4] = mesh->vertex[(index * 8) + 4];
			mesh->final_vao[(index * 17) + 5] = mesh->vertex[(index * 8) + 5];
			mesh->final_vao[(index * 17) + 6] = mesh->vertex[(index * 8) + 6];
			mesh->final_vao[(index * 17) + 7] = mesh->vertex[(index * 8) + 7];
		}
	}
}

static void	mesh_pack_vao_data_push_texture(t_mesh *mesh, size_t index)
{
	if (mesh)
	{
		if (mesh->texture)
		{
			mesh->final_vao[(index * 17) + 8] = mesh->face[(index * 3) + 1];
			mesh->final_vao[(index * 17) + 9] = mesh->face[(index * 3) + 4];
			mesh->final_vao[(index * 17) + 10] = mesh->face[(index * 3) + 7];
		}
	}

}

static void	mesh_pack_vao_data_push_normal(t_mesh *mesh, size_t index)
{
	if (mesh)
	{
		if (mesh->normal)
		{
			mesh->final_vao[(index * 17) + 11] = mesh->face[(index * 3) + 2];
			mesh->final_vao[(index * 17) + 12] = mesh->face[(index * 3) + 5];
			mesh->final_vao[(index * 17) + 13] = mesh->face[(index * 3) + 8];
		}
	}
}

static void	mesh_pack_vao_data_push_space(t_mesh *mesh, size_t index)
{
	if (mesh)
	{
		if (mesh->space)
		{
			mesh->final_vao[(index * 17) + 14] = mesh->space[(index * 3)];
			mesh->final_vao[(index * 17) + 15] = mesh->space[(index * 3) + 1];
			mesh->final_vao[(index * 17) + 16] = mesh->space[(index * 3) + 2];
		}
	}
}

bool		mesh_pack_vao_data(t_mesh *mesh)
{
	size_t	i;

	if (mesh && !(i = 0))
	{
		scop_log("Packing data for a big VAO :) ...\n", NULL);
		if (!(mesh->final_vao = ft_memalloc(sizeof(GLfloat) \
											* mesh->n_vertex[1] * 17)))
			return (error_bool("[ERROR mesh_pack_vao_data]\t" \
			"Could not allocate memory for the VAO data packing!\n"));
		while (i < mesh->n_vertex[0])
		{
			mesh_pack_vao_data_push_pos_hue(mesh, i);
			mesh_pack_vao_data_push_texture(mesh, i);
			mesh_pack_vao_data_push_normal(mesh, i);
			mesh_pack_vao_data_push_space(mesh, i);
			i++;
		}
		scop_log("Successfully packed VAO data!\n", NULL);
		return (true);
	}
	return (error_bool("[ERROR mesh_pack_vao_data]\tNULL mesh pointer!\n"));
}
