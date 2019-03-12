/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_mouse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:35:13 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/12 11:31:35 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		cb_mouse_pos(GLFWwindow *window, \
									double xpos, \
									double ypos)
{
	t_scop	*env;
	double	offset[2];
	return ;
	env = glfwGetWindowUserPointer(window);
	if (!env->mouse->ready)
	{
		env->mouse->last[0] = xpos;
		env->mouse->last[1] = ypos;
		env->mouse->ready = true;
	}
	offset[0] = (xpos - env->mouse->last[0]);
	offset[1] = (env->mouse->last[1] - ypos);
	env->mouse->last[0] = xpos;
	env->mouse->last[1] = ypos;


	env->mat->cam_euler[0] += offset[0];
	env->mat->cam_euler[1] += offset[1];

	if (env->mat->cam_euler[1] > 89.0f)
		env->mat->cam_euler[1] = 89.0f;
	if (env->mat->cam_euler[1] < -89.0f)
		env->mat->cam_euler[1] = -89.0f;

	env->cam->front.x = cos(env->mat->cam_euler[0] * DEG2RAD) * cos(env->mat->cam_euler[1] * DEG2RAD);
	env->cam->front.y = sin(env->mat->cam_euler[1] * DEG2RAD);
	env->cam->front.z = sin(env->mat->cam_euler[0] * DEG2RAD) * cos(env->mat->cam_euler[1] * DEG2RAD);
	cam_update(env);
	env->mat->view = cam_get_lookat(env->cam);
}

void		cb_mouse_btn(GLFWwindow *window, \
										int button, \
										int action, \
										int mods)
{
	t_scop	*env;

	env = glfwGetWindowUserPointer(window);

	fprintf(stdout, "debug mouse button cb -> btn = %d | action = %d | mods = %d\n", \
			button, action, mods);
}

void		cb_mouse_scroll(GLFWwindow *window, \
										double x_offset, \
										double y_offset)
{
	t_scop	*env;

	env = glfwGetWindowUserPointer(window);
	x_offset = 0.0f;
	if (env->cam->cam_mod[0] >= 30.0f && env->cam->cam_mod[0] <= 120.0f)
		env->cam->cam_mod[0] -= y_offset;
	if (env->cam->cam_mod[0] <= 30.0f)
		env->cam->cam_mod[0] = 30.0f;
	if (env->cam->cam_mod[0] >= 120.0f)
		env->cam->cam_mod[0] = 120.0f;
	env->mat->projection = mat4_set_perspective(env->cam->cam_mod[0], \
				env->win_res[2], env->cam->cam_mod[1], env->cam->cam_mod[2]);
}
