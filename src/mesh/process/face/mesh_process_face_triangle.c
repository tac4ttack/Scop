/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_process_face_triangle.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:42:33 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/06 12:12:11 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		mesh_process_face_triangle(t_mesh *mesh, char **split, int index)
{
	int		i;
	int		mod;
	bool	fail;

	if (mesh && split && !(fail = false))
	{
		i = 0;
		if ((mod = mesh_process_face_type_get(*split)) == -1)
			return (error_bool("[ERROR mesh_process_face_triangle]\t" \
			"Face element type recognized!\n"));
		while (i++ < 3)
		{
			if (mod != mesh_process_face_type_get(*split))
				return (error_bool("[ERROR mesh_process_face_triangle]\t"
				"Face element type has changed!\n"));
			fail = !mesh_process_face_data_dispatch(mesh, *split, mod, index);
			if (fail)
				return (error_bool("[ERROR mesh_process_face_triangle]\t"
				"Failed to retrieve face element data!\n"));
			index += 3;
			split++;
		}
		return (true);
	}
	return (error_bool("[ERROR mesh_process_face_triangle]\t" \
	"NULL mesh or split pointer!\n"));
}
