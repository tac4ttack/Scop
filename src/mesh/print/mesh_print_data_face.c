/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_print_data_face.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 15:09:07 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/06 12:07:59 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		mesh_print_data_face(t_mesh *mesh)
{
	size_t		i;

	if (mesh && mesh->face && !(i = 0))
	{
		scop_log("\nFace data =\n-------------\n", NULL);
		while (i < mesh->n_face[1])
		{
			scop_log("f[%zu]\t=\t%d/%d/%d %d/%d/%d %d/%d/%d\n", i,
			mesh->face[(i * 9)], \
			mesh->face[(i * 9) + 1], \
			mesh->face[(i * 9) + 2], \
			mesh->face[(i * 9) + 3], \
			mesh->face[(i * 9) + 4], \
			mesh->face[(i * 9) + 5], \
			mesh->face[(i * 9) + 6], \
			mesh->face[(i * 9) + 7], \
			mesh->face[(i * 9) + 8]);
			i++;
		}
	}
}
