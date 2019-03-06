/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_print_data_vertex.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 15:07:38 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/06 11:59:43 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		mesh_print_data_vertex(t_mesh *mesh)
{
	size_t	i;

	if (mesh && mesh->vertex && !(i = 0))
	{
		scop_log("\nVertex data =\n-------------\n", NULL);
		while (i < mesh->n_vertex[1])
		{
			scop_log("v[%d][%d|%d|%d|%d|%d|%d|%d|%d]" \
					"\t=\t%f %f %f %f %f %f %f %f\n", \
					i, (i * 8), (i * 8) + 1, (i * 8) + 2, (i * 8) + 3, \
					i, (i * 8) + 4, (i * 8) + 5, (i * 8) + 6, (i * 8) + 7, \
					mesh->vertex[(i * 8)], mesh->vertex[(i * 8) + 1], \
					mesh->vertex[(i * 8) + 2], mesh->vertex[(i * 8) + 3], \
					mesh->vertex[(i * 8) + 4], mesh->vertex[(i * 8) + 5],\
					mesh->vertex[(i * 8) + 6], mesh->vertex[(i * 8) + 7]);
			i++;
		}
	}
}
