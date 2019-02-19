/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_print_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:36:33 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/19 17:42:56 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	mesh_print_data_vertex(t_mesh *mesh)
{
	int		i;

	if (mesh->vertex)
	{
		i = 0;
		while ((unsigned int)i < (unsigned int)(mesh->n_vertex))
		{
			fprintf(stdout, "v[%d\t%d\t%d\t%d]\t=\t%f\t%f\t%f\t%f\n", (i * 4), \
			(i * 4) + 1, (i * 4) + 2, (i * 4) + 3, mesh->vertex[(i * 4)], \
			mesh->vertex[(i * 4) + 1], mesh->vertex[(i * 4) + 2], mesh->vertex[(i * 4) + 3]);
			i++;
		}
	}
}

static void	mesh_print_data_face(t_mesh *mesh)
{
	int		i;

	if (mesh->face)
	{
		i = 0;
		while ((unsigned int)i < (unsigned int)(mesh->n_vertex))
		{
			fprintf(stdout, "v[%d\t%d\t%d\t%d]\t=\t%f\t%f\t%f\t%f\n", (i * 4), \
			(i * 4) + 1, (i * 4) + 2, (i * 4) + 3, mesh->vertex[(i * 4)], \
			mesh->vertex[(i * 4) + 1], mesh->vertex[(i * 4) + 2], mesh->vertex[(i * 4) + 3]);
			i++;
		}
	}
}

void		mesh_print_data(t_mesh *mesh)
{
	if (mesh->vertex)
		mesh_print_data_vertex(mesh);
	if (mesh->face)
		mesh_print_data_face(mesh);
}
