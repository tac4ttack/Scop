/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_print_data_prepack_vao.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 12:17:13 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/24 11:22:59 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		mesh_print_data_packed_vao(t_obj *mesh)
{
	size_t	i;

	if (mesh && mesh->prepack_vao && !(i = 0))
	{
		scop_log("\nVertex VAO data =\n-----------------\nvao[n]\t=\t[VXn VYn" \
		" VZn VWn] | [VRn VGn VBn VAn] | [VTUn VTVn VTWn] | [VNIn VNJn VNKn] " \
		" [VPUn VPVn VPWn]\n", NULL);
		while (i < mesh->n_vertex[0])
		{
			scop_log("vao[%d]\t=\t%f %f %f %f | %f %f %f %f | %f %f %f | "\
			"%f %f %f | %f %f %f\n", i, mesh->prepack_vao[(i * 17)], \
			mesh->prepack_vao[(i * 17) + 1], mesh->prepack_vao[(i * 17) + 2], \
			mesh->prepack_vao[(i * 17) + 3], mesh->prepack_vao[(i * 17) + 4], \
			mesh->prepack_vao[(i * 17) + 5], mesh->prepack_vao[(i * 17) + 6], \
			mesh->prepack_vao[(i * 17) + 7], mesh->prepack_vao[(i * 17) + 8], \
			mesh->prepack_vao[(i * 17) + 9], mesh->prepack_vao[(i * 17) + 10], \
			mesh->prepack_vao[(i * 17) + 11], \
			mesh->prepack_vao[(i * 17) + 12], \
			mesh->prepack_vao[(i * 17) + 13], \
			mesh->prepack_vao[(i * 17) + 14], \
			mesh->prepack_vao[(i * 17) + 15], \
			mesh->prepack_vao[(i * 17) + 16]);
			i++;
		}
	}
}
