/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_print_data_prepack_vao.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 12:17:13 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/27 18:10:10 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
**	VAO buffer structure is:
**	vao[n] = VXn VYn VZn VWn | VRn VGn VBn VAn | VTUn VTVn VTWn | VNIn VNJn VNKn
*/

void		mesh_print_data_packed_vao(t_scop *env)
{
	size_t	i;

	if (env && env->mesh && env->prepack_vao && !(i = 0))
	{
		scop_log("\nVertex VAO data =\n-----------------\n", NULL);
		while (i < env->mesh->n_face[0] * 3)
		{
			scop_log("vao[%d]\t=\t%f %f %f %f | %f %f %f %f | %f %f %f | "\
			"%f %f %f\n", i, env->prepack_vao[(i * VAOLEN)], \
			env->prepack_vao[(i * VAOLEN) + 1], \
			env->prepack_vao[(i * VAOLEN) + 2], \
			env->prepack_vao[(i * VAOLEN) + 3], \
			env->prepack_vao[(i * VAOLEN) + 4], \
			env->prepack_vao[(i * VAOLEN) + 5], \
			env->prepack_vao[(i * VAOLEN) + 6], \
			env->prepack_vao[(i * VAOLEN) + 7], \
			env->prepack_vao[(i * VAOLEN) + 8], \
			env->prepack_vao[(i * VAOLEN) + 9], \
			env->prepack_vao[(i * VAOLEN) + 10], \
			env->prepack_vao[(i * VAOLEN) + 11], \
			env->prepack_vao[(i * VAOLEN) + 12], \
			env->prepack_vao[(i * VAOLEN) + 13]);
			i++;
		}
	}
}
