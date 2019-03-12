/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_translate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:55:44 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/12 10:56:00 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	cam_translate(t_scop *env, int key)
{
	if (env)
	{
		if (key == GLFW_KEY_R)
			env->cam->pos = vec3f(0.0f, 0.0f, 0.0f);
		else if (key == GLFW_KEY_W)
			env->cam->pos = vec3f_add(env->cam->pos, \
							vec3f_mul_scalar(env->cam->front, env->cam->speed));
		else if (key == GLFW_KEY_S)
			env->cam->pos = vec3f_sub(env->cam->pos, \
							vec3f_mul_scalar(env->cam->front, env->cam->speed));
		else if (key == GLFW_KEY_A)
			env->cam->pos = vec3f_sub(env->cam->pos, vec3f_mul_scalar( \
				vec3f_normalize(vec3f_cross(env->cam->front, env->cam->up)), \
				env->cam->speed));
		else if (key == GLFW_KEY_D)
			env->cam->pos = vec3f_add(env->cam->pos, vec3f_mul_scalar( \
				vec3f_normalize(vec3f_cross(env->cam->front, env->cam->up)), \
				env->cam->speed));
		else if (key == GLFW_KEY_SPACE)
			;
		else if (key == GLFW_KEY_C)
			;
		env->mat->view = mat4_set_lookat(env->cam->pos, \
					vec3f_add(env->cam->pos, env->cam->front), env->cam->up);
		return (true);
	}
	return (false);
}
