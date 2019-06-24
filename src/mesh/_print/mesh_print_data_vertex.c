/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_print_data_vertex.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 15:07:38 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/24 11:22:59 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		mesh_print_data_vertex(t_obj *mesh)
{
	size_t	i;

	if (mesh && mesh->vertex && !(i = 0))
	{
		scop_log("\nVertex data =\n-------------\n", NULL);
		while (i < mesh->n_vertex[1])
		{
			scop_log("v[%d]\t=\t%f %f %f %f %f %f %f %f\n", i, \
					mesh->vertex[(i * 8)], \
					mesh->vertex[(i * 8) + 1], \
					mesh->vertex[(i * 8) + 2], \
					mesh->vertex[(i * 8) + 3], \
					mesh->vertex[(i * 8) + 4], \
					mesh->vertex[(i * 8) + 5], \
					mesh->vertex[(i * 8) + 6], \
					mesh->vertex[(i * 8) + 7]);
			i++;
		}
	}
}
