/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_translate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:55:44 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/14 13:51:00 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	cam_translate(t_scop *env, int key)
{
	if (env)
	{
		if (key == GLFW_KEY_R)
			env->world->cam_position = vec3f(0.0f, 0.0f, 0.0f);
		else if (key == GLFW_KEY_W)
			env->world->cam_position = vec3f_add(env->world->cam_position, \
			 	vec3f_mul_scalar(env->world->cam_front, env->world->cam_speed));
		else if (key == GLFW_KEY_S)
			env->world->cam_position = vec3f_sub(env->world->cam_position, \
				vec3f_mul_scalar(env->world->cam_front, env->world->cam_speed));
		else if (key == GLFW_KEY_A)
			env->world->cam_position = vec3f_sub(env->world->cam_position, \
				vec3f_mul_scalar(vec3f_normalize(vec3f_cross( \
				env->world->cam_front, env->world->cam_up)), \
				env->world->cam_speed));
		else if (key == GLFW_KEY_D)
			env->world->cam_position = vec3f_add(env->world->cam_position, \
				vec3f_mul_scalar(vec3f_normalize(vec3f_cross( \
				env->world->cam_front, env->world->cam_up)), \
				env->world->cam_speed));
		else if (key == GLFW_KEY_SPACE)
			;
		else if (key == GLFW_KEY_C)
			;
		return (true);
	}
	return (false);
}
