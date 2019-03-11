/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_mouse_callback.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:24:05 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/11 18:39:30 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		glfw_mouse_pos_callback(GLFWwindow *window, \
									double xpos, \
									double ypos)
{
	t_scop	*env;
	double	offset[2];

	env = glfwGetWindowUserPointer(window);
	if (!env->mouse->ready)
	{
		env->mouse->last[0] = xpos;
		env->mouse->last[1] = ypos;
		env->mouse->ready = true;
	}
	offset[0] = (xpos - env->mouse->last[0]) * env->mouse->sensitivity;
	offset[1] = (env->mouse->last[1] - ypos) * env->mouse->sensitivity;
	env->mouse->last[0] = xpos;
	env->mouse->last[1] = ypos;
	env->cam->euler[0] += offset[0];
	env->cam->euler[1] += offset[1];

	if (env->cam->euler[1] > 89.0f)
		env->cam->euler[1] = 89.0f;
	if (env->cam->euler[1] < -89.0f)
		env->cam->euler[1] = -89.0f;

	env->cam->front.x = cos(env->cam->euler[0] * DEG2RAD) * cos(env->cam->euler[1] * DEG2RAD);
	env->cam->front.y = sin(env->cam->euler[1] * DEG2RAD);
	env->cam->front.z = sin(env->cam->euler[0] * DEG2RAD) * cos(env->cam->euler[1] * DEG2RAD);
	env->cam->front = vec3f_normalize(env->cam->front);
	env->mat->view = mat4_set_lookat(env->cam->pos, env->cam->front, env->cam->up);
}

void		glfw_mouse_button_callback(GLFWwindow *window, \
										int button, \
										int action, \
										int mods)
{
	t_scop	*env;

	env = glfwGetWindowUserPointer(window);

	fprintf(stdout, "debug mouse button cb -> btn = %d | action = %d | mods = %d\n", \
			button, action, mods);
}

void		glfw_mouse_scroll_callback(GLFWwindow *window, \
										double x_offset, \
										double y_offset)
{
	t_scop	*env;

	env = glfwGetWindowUserPointer(window);
	x_offset = 0.0f;
	if (y_offset > 0.0f)
		env->cam->cam_mod[0] += (env->cam->cam_mod[0] >= 150.0f ? 0.0f : 1.0f);
	else if (y_offset < 0.0f)
		env->cam->cam_mod[0] -= (env->cam->cam_mod[0] <= 30.0f ? 0.0f : 1.0f);
	env->mat->projection = mat4_set_perspective(env->cam->cam_mod[0], \
				env->win_res[2], env->cam->cam_mod[1], env->cam->cam_mod[2]);
}
