/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_process_face_quad.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:08:01 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/28 18:38:47 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		mesh_process_face_quad(t_mesh *mesh, char **split, int index)
{
	int		mod;
	GLint	triangles[2][3];

	if (mesh && split)
	{
		fprintf(stdout, "index = %d\nsplit = %s\n", index, *split);
		if ((mod = mesh_process_face_type_get(*split)) == -1)
			return (error_bool("[ERROR mesh_process_face_quad]\t" \
			"Face element type not recognized!\n"));
		fprintf(stdout, "DEBUG FACE MOD = %d\n", mod);
		return (true);
	}
	return (error_bool("[ERROR mesh_process_face_quad]\t" \
	"NULL mesh or split pointer!\n"));
}
