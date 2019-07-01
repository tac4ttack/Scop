/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_mouse_btn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 11:24:51 by fmessina          #+#    #+#             */
/*   Updated: 2019/07/01 11:29:58 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	cb_mouse_btn_set(t_scop *env, int button, int action)
{
	if (env)
	{
		if (action == GLFW_PRESS)
		{
			if (button == GLFW_MOUSE_BUTTON_LEFT)
			{
				env->mouse->lmb = 1;
				input_mouse_rot(&env->mouse->prev, env->mouse->dummy);
			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT)
				env->mouse->rmb = 1;
			else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
				env->mouse->mmb = 1;
		}
		else if (action == GLFW_RELEASE)
		{
			if (button == GLFW_MOUSE_BUTTON_LEFT)
				env->mouse->lmb = 0;
			else if (button == GLFW_MOUSE_BUTTON_RIGHT)
				env->mouse->rmb = 0;
			else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
				env->mouse->mmb = 0;
		}
	}
}

void		cb_mouse_btn(GLFWwindow *window, \
						int button, \
						int action, \
						int mods)
{
	t_scop	*env;

	env = glfwGetWindowUserPointer(window);
	if (button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT \
		|| button == GLFW_MOUSE_BUTTON_MIDDLE)
		cb_mouse_btn_set(env, button, action);
	if (DEBUG_SCOP)
		fprintf(stdout, "[DEBUG]: mouse button callback -> " \
						"btn = %d | action = %d | mods = %d\n", \
						button, action, mods);
}
