/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:55:38 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/13 16:22:35 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

// t_mat4	cam_get_lookat(t_camera *c)
// {
// 	return (mat4_set_lookat(c->pos, vec3f_add(c->pos, c->front), c->world_up));
// }

bool	cam_update(t_scop *env)
{
	if (env)
	{
		// Calculate the new Front vector
		// env->cam->front.x = cos(env->mat->cam_euler[0] * DEG2RAD) * cos(env->mat->cam_euler[1] * DEG2RAD);
		// env->cam->front.y = sin(env->mat->cam_euler[0] * DEG2RAD);
		// env->cam->front.z = sin(env->mat->cam_euler[1] * DEG2RAD) * cos(env->mat->cam_euler[0] * DEG2RAD);
		// env->cam->front = vec3f_normalize(env->cam->front);

		// // Also re-calculate the Right and Up vector
		// env->cam->right = vec3f_normalize(vec3f_cross(env->cam->front, env->cam->world_up));
		// env->cam->up = vec3f_normalize(vec3f_cross(env->cam->right, env->cam->front));
		return (true);
	}
	return (false);
}

bool	cam_look(t_scop *env, int key)
{
	// totally broken!
	if (env)
	{
		if (key == GLFW_KEY_UP)
		;
		// 	env->mat->cam_euler[0] += 1.0;
		// else if (key == GLFW_KEY_DOWN)
		// 	env->mat->cam_euler[0] -= 1.0;
		// else if (key == GLFW_KEY_LEFT)
		// 	env->mat->cam_euler[1] += 1.0;
		// else if (key == GLFW_KEY_RIGHT)
		// 	env->mat->cam_euler[1] -= 1.0;
		// else if (key == GLFW_KEY_RIGHT_CONTROL)
		// 	env->mat->cam_euler[2] += 1.0;
		// else if (key == GLFW_KEY_RIGHT)
		// 	env->mat->cam_euler[2] -= 1.0;
		// fprintf(stdout, "debug cam look x = %f y = %f z = %f\n",
		// env->mat->cam_euler[0], env->mat->cam_euler[1], env->mat->cam_euler[2]);
		// cam_update(env);
		// env->mat->view = cam_get_lookat(env->cam);
		return (true);
	}
	return (false);
}
