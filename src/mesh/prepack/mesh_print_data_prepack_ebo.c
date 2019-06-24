/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_print_data_prepack_ebo.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 12:17:13 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/24 11:22:59 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		mesh_print_data_packed_ebo(t_obj *mesh)
{
	size_t	i;

	if (mesh && mesh->prepack_ebo && !(i = 0))
	{
		scop_log("\nFace element EBO data =\n-----------------------\n", NULL);
		while (i < mesh->n_face[0])
		{
			scop_log("ebo[%d]\t=\t%d %d %d\n", i, \
			mesh->prepack_ebo[(i * 3)], \
			mesh->prepack_ebo[(i * 3) + 1], \
			mesh->prepack_ebo[(i * 3) + 2]);
			i++;
		}
	}
}
