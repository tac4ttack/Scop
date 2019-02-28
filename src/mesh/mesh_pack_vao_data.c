/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_pack_vao_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:33:55 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/28 12:16:57 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool mesh_pack_vao_data(t_mesh *mesh)
{
	if (mesh)
	{
		scop_log("Packing data for a big VAO :) ...\n", NULL);
		if (!(mesh->final_vao = ft_memalloc(sizeof(GLfloat) \
											* mesh->n_vertex[1] * 17)))
			return (error_bool("[ERROR mesh_pack_vao_data]\t" \
			"Could not allocate memory for the VAO data packing!\n"));
		scop_log("Successfully packed VAO data!\n", NULL);
		return (true);
	}
	return (error_bool("[ERROR mesh_pack_vao_data]\tNULL mesh pointer!\n"));
}
