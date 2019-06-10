/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_translate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:49:59 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/10 15:04:08 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		mesh_translate(t_scop *env, int key)
{
	t_mat4	trans;

	trans = mat4_set_identity();
	if (env)
	{
		if (key == GLFW_KEY_Y)
			env->world->mesh_position = vec3f_add(env->world->mesh_position, \
												vec3f(0.0, 0.1, 0.0));
		else if (key == GLFW_KEY_H)
			env->world->mesh_position = vec3f_add(env->world->mesh_position, \
												vec3f(0.0, -0.1, 0.0));
		else if (key == GLFW_KEY_G)
			env->world->mesh_position = vec3f_add(env->world->mesh_position, \
												vec3f(-0.1, 0.00, 0.0));
		else if (key == GLFW_KEY_J)
			env->world->mesh_position = vec3f_add(env->world->mesh_position, \
												vec3f(0.1, 0.00, 0.0));
		else if (key == GLFW_KEY_T)
			env->world->mesh_position = vec3f_add(env->world->mesh_position, \
												vec3f(0.0, 0.00, -0.1));
		else if (key == GLFW_KEY_U)
			env->world->mesh_position = vec3f_add(env->world->mesh_position, \
												vec3f(0.0, 0.00, 0.1));
		return (true);
	}
	return (error_bool("[ERROR mesh_translate]\tNULL Scop pointer!\n"));
}
