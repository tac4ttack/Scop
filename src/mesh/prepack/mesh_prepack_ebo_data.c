/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_prepack_ebo_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:33:55 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/06 14:21:05 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		mesh_prepack_ebo_data(t_mesh *mesh)
{
	size_t	i;

	if (mesh && !(i = 0))
	{
		scop_log("Packing data for a EBO :) ...\n", NULL);
		if (!(mesh->prepack_ebo = ft_memalloc(sizeof(GLint) \
												* mesh->n_face[0] * 3)))
			return (error_bool("[ERROR mesh_prepack_ebo_data]\t" \
			"Could not allocate memory for the EBO data packing!\n"));
		while (i < mesh->n_face[0])
		{
			mesh->prepack_ebo[(i * 3)] = mesh->face[(i * 3)];
			mesh->prepack_ebo[(i * 3) + 1] = mesh->face[(i * 3) + 3];
			mesh->prepack_ebo[(i * 3) + 2] = mesh->face[(i * 3) + 6];
			i++;
		}
		scop_log("Successfully packed EBO data!\n", NULL);
		return (true);
	}
	return (error_bool("[ERROR mesh_prepack_ebo_data]\tNULL mesh pointer!\n"));
}
