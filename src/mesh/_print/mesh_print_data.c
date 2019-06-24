/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_print_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:36:33 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/24 11:28:18 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	mesh_print_data(t_obj *mesh)
{
	if (mesh->vertex)
		mesh_print_data_vertex(mesh);
	if (mesh->normal)
		mesh_print_data_normal(mesh);
	if (mesh->texture)
		mesh_print_data_texture(mesh);
	if (mesh->space)
		mesh_print_data_space(mesh);
	if (mesh->face)
		mesh_print_data_face(mesh);
	if (mesh->prepack_vao)
		mesh_print_data_packed_vao(mesh);
	if (mesh->prepack_ebo)
		mesh_print_data_packed_ebo(mesh);
	scop_log("\n\n", NULL);
}
