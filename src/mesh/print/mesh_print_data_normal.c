/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_print_data_normal.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:38:08 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/06 14:45:13 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		mesh_print_data_normal(t_mesh *mesh)
{
	size_t	i;

	if (mesh && !(i = 0))
	{
		scop_log("\nVertices normals data =\n------------------------\n");
		while (i < mesh->n_normal[1])
		{
			scop_log("vn[%d]\t=\t%f %f %f\n", i, \
			mesh->normal[(i * 3)], \
			mesh->normal[(i * 3) + 1], \
			mesh->normal[(i * 3) + 2]);
			i++;
		}
	}
}
