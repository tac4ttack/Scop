/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_print_data_texture.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:17:46 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/24 11:22:59 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		mesh_print_data_texture(t_obj *mesh)
{
	size_t	i;

	if (mesh && !(i = 0))
	{
		scop_log("\nTexture coordinates data =\n--------------------------\n");
		while (i < mesh->n_texture[1])
		{
			scop_log("vt[%d]\t=\t%f %f %f\n", i, \
			mesh->texture[(i * 3)], \
			mesh->texture[(i * 3) + 1], \
			mesh->texture[(i * 3) + 2]);
			i++;
		}
	}
}
