/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_translate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:49:59 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/14 12:56:41 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		mesh_translate(t_scop *env, int key)
{
	t_mat4	trans;

	trans = mat4_set_identity();
	if (env)
	{
		if (key == GLFW_KEY_KP_8)
			env->world->mesh_position = vec3f_add(env->world->mesh_position, vec3f(0.0, 0.1, 0.0));
			// trans = mat4_set_translation(vec3f(0.0, 0.1, 0.0));
		else if (key == GLFW_KEY_KP_5)
			env->world->mesh_position = vec3f_add(env->world->mesh_position, vec3f(0.0, -0.1, 0.0));
			// trans = mat4_set_translation(vec3f(0.0, -0.1, 0.0));
		else if (key == GLFW_KEY_KP_4)
			env->world->mesh_position = vec3f_add(env->world->mesh_position, vec3f(-0.1, 0.00, 0.0));
			// trans = mat4_set_translation(vec3f(-0.1, 0.00, 0.0));
		else if (key == GLFW_KEY_KP_6)
			env->world->mesh_position = vec3f_add(env->world->mesh_position, vec3f(0.1, 0.00, 0.0));
			// trans = mat4_set_translation(vec3f(0.1, 0.00, 0.0));
		else if (key == GLFW_KEY_KP_9)
			env->world->mesh_position = vec3f_add(env->world->mesh_position, vec3f(0.0, 0.00, -0.1));
			// trans = mat4_set_translation(vec3f(0.0, 0.00, -0.1));
		else if (key == GLFW_KEY_KP_7)
			env->world->mesh_position = vec3f_add(env->world->mesh_position, vec3f(0.0, 0.00, 0.1));
			// trans = mat4_set_translation(vec3f(0.0, 0.00, 0.1));
		// env->world->mesh_translation = mat4_mul(trans, env->world->mesh_translation);

		env->world->mesh_translation = mat4_set_translation(env->world->mesh_position);
		// env->world->mesh_translation = mat4_transpose(mat4_set_translation(env->world->mesh_position));
		return (true);
	}
	return (error_bool("[ERROR mesh_translate]\tNULL Scop pointer!\n"));
}
