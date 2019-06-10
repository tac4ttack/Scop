/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_process_face_quad.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:08:01 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/06 11:03:19 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		mesh_process_face_quad(t_mesh *mesh, char **split, int index)
{
	char	*new[2][3];

	if (mesh && split)
	{
		new[0][0] = split[0];
		new[0][1] = split[1];
		new[0][2] = split[2];
		new[1][0] = split[0];
		new[1][1] = split[2];
		new[1][2] = split[3];
		if (!(mesh_process_face_triangle(mesh, new[0], index)))
			return (error_bool("[ERROR mesh_process_face_quad]\t" \
			"Failed to retrieve data from first new triangle!\n"));
		index = (++mesh->n_face[1] - 1) * 9;
		if (!(mesh_process_face_triangle(mesh, new[1], index)))
			return (error_bool("[ERROR mesh_process_face_quad]\t" \
			"Failed to retrieve data from second new triangle!\n"));
		return (true);
	}
	return (error_bool("[ERROR mesh_process_face_quad]\t" \
	"NULL mesh or split pointer!\n"));
}
