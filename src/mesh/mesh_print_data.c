/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_print_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:36:33 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/23 19:03:00 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		mesh_print_data(t_mesh *mesh)
{
	if (mesh->vertex)
		mesh_print_data_vertex(mesh);
	if (mesh->face)
	{
		mesh_print_data_face_type(mesh);
		mesh_print_data_face(mesh);
		scop_log("\n\n", NULL);
	}
}
