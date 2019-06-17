/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:49:59 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/17 11:23:05 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		mesh_scale(t_scop *env, int key)
{
	t_mat4	trans;

	trans = mat4_set_identity();
	if (env)
	{
		if (key == GLFW_KEY_M)
			env->world->mesh_scaler = vec3f_add_scalar( \
											env->world->mesh_scaler, 0.1f);
		else if (key == GLFW_KEY_N)
			env->world->mesh_scaler = vec3f_sub_scalar( \
											env->world->mesh_scaler, 0.1f);
		return (true);
	}
	return (error_bool("[ERROR mesh_scale]\tNULL Scop pointer!\n"));
}
