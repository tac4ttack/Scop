/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_print_data_prepack_vao.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 12:17:13 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/24 11:57:35 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		mesh_print_data_packed_vao(t_scop *env)
{
	size_t	i;

	if (env && env->mesh && env->prepack_vao && !(i = 0))
	{
		scop_log("\nVertex VAO data =\n-----------------\nvao[n]\t=\t[VXn VYn" \
		" VZn VWn] | [VRn VGn VBn VAn] | [VTUn VTVn VTWn] | [VNIn VNJn VNKn] " \
		" [VPUn VPVn VPWn]\n", NULL);
		while (i < env->mesh->n_vertex[0])
		{
			scop_log("vao[%d]\t=\t%f %f %f %f | %f %f %f %f | %f %f %f | "\
			"%f %f %f | %f %f %f\n", i, env->prepack_vao[(i * 17)], \
			env->prepack_vao[(i * 17) + 1], env->prepack_vao[(i * 17) + 2], \
			env->prepack_vao[(i * 17) + 3], env->prepack_vao[(i * 17) + 4], \
			env->prepack_vao[(i * 17) + 5], env->prepack_vao[(i * 17) + 6], \
			env->prepack_vao[(i * 17) + 7], env->prepack_vao[(i * 17) + 8], \
			env->prepack_vao[(i * 17) + 9], env->prepack_vao[(i * 17) + 10], \
			env->prepack_vao[(i * 17) + 11], \
			env->prepack_vao[(i * 17) + 12], \
			env->prepack_vao[(i * 17) + 13], \
			env->prepack_vao[(i * 17) + 14], \
			env->prepack_vao[(i * 17) + 15], \
			env->prepack_vao[(i * 17) + 16]);
			i++;
		}
	}
}
