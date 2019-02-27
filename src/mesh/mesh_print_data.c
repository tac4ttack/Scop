/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_print_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:36:33 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/26 14:37:07 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	mesh_print_data(t_mesh *mesh)
{
	if (mesh->vertex)
		mesh_print_data_vertex(mesh);
	if (mesh->normal)
		mesh_print_data_normal(mesh);
	if (mesh->texture)
		mesh_print_data_texture(mesh);
	if (mesh->face)
	{
		mesh_print_data_face_type(mesh);
		mesh_print_data_face(mesh);
	}
	scop_log("\n\n", NULL);
}
