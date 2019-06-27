/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:07:37 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/27 10:40:48 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool			time_update(t_scop *env)
{
	GLfloat		current;

	current = glfwGetTime();
	if (env)
	{
		env->time_delta = current - env->time_last;
		if (env->auto_rot)
			env->world->mesh_orient = quat_mul(env->world->mesh_orient, \
						quat_rot(vec3f(0.0, -1.0, 0.0), env->auto_rot_speed));
		env->time_frames++;
		if (env->time_delta >= 0.50f)
		{
			sprintf(env->win_title, "Scop - [%f ms/frame | %d fps]", \
			1000.0 / (double)env->time_frames, env->time_frames);
			glfwSetWindowTitle(env->win, env->win_title);
			env->time_frames = 0;
			env->time_last += 1.0f;
			env->world->cam_speed = 0.5f * env->time_delta;
		}
		return (true);
	}
	return (error_bool("[ERROR time_update]\tNULL Scop pointer!\n"));
}
