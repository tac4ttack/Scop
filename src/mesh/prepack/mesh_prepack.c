/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_prepack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:07:32 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/24 11:43:06 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	mesh_prepack(t_scop *env)
{
	if (env)
	{
		if (env->mesh->n_face[0] > 1)
			if (!(mesh_prepack_ebo_data(env)))
				return (error_bool("[ERROR mesh_prepack]\t" \
				"Failed to pack EBO data!\n"));
		if (!(mesh_prepack_get_center_axis(env->mesh)) \
			|| !mesh_prepack_center_vertices(env->mesh))
			return (error_bool("[ERROR mesh_prepack]\t" \
			"Failed to recenter mesh and compute its main axis!\n"));
		if (!(mesh_prepack_vao_data(env)))
			return (error_bool("[ERROR mesh_prepack]\t" \
			"Failed to pack VAO data!\n"));
		return (true);
	}
	return (error_bool("[ERROR mesh_prepack]\tNULL env pointer!\n"));
}
