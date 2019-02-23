/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_print_data_vertex.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 15:07:38 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/23 15:08:08 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		mesh_print_data_vertex(t_mesh *mesh)
{
	size_t	i;

	if (mesh->vertex)
	{
		i = 0;
		scop_log("\nVertex data =\n-------------\n", NULL);
		while (i < mesh->n_vertex[1])
		{
			scop_log("v[%d][%d\t%d\t%d\t%d]\t=\t%f\t%f\t%f\t%f\n", \
					i, (i * 4), (i * 4) + 1, (i * 4) + 2, (i * 4) + 3, \
					mesh->vertex[(i * 4)], mesh->vertex[(i * 4) + 1], \
					mesh->vertex[(i * 4) + 2], mesh->vertex[(i * 4) + 3]);
			i++;
		}
	}
}
