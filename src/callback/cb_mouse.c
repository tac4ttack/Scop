/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_mouse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:35:13 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/30 16:18:56 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		cb_mouse_pos(GLFWwindow *window, \
									double xpos, \
									double ypos)
{
	t_scop	*env;

	env = glfwGetWindowUserPointer(window);
	if (env->mouse->lmb)
	{
		trackball(env->mouse->prev_rot, \
			env->mouse->rot_speed * (2.0f * env->mouse->last[0] - env->win_res[0]) / (float)env->win_res[0],
        	env->mouse->rot_speed * (env->win_res[1] - 2.0f * env->mouse->last[0]) / (float)env->win_res[1],
			env->mouse->rot_speed * (2.0f * (float)xpos - env->win_res[0]) / (float)env->win_res[0],
			env->mouse->rot_speed * (env->win_res[1] - 2.0f * (float)ypos) / (float)env->win_res[1]);
		float mesh_q[4] = {env->world->mesh_orient.w, \
							env->world->mesh_orient.x, \
							env->world->mesh_orient.y, \
							env->world->mesh_orient.z};
		
		add_quats(env->mouse->prev_rot, mesh_q, mesh_q);
		env->world->mesh_orient.w = mesh_q[0];
		env->world->mesh_orient.x = mesh_q[1];	
		env->world->mesh_orient.y = mesh_q[2];	
		env->world->mesh_orient.z = mesh_q[3];	
	}
	env->mouse->last[0] = xpos;
	env->mouse->last[1] = ypos;
}

static void cb_mouse_btn_set(t_scop *env, int button, int action)
{
	if (env)
	{
		if (action == GLFW_PRESS)
		{
			if (button == GLFW_MOUSE_BUTTON_LEFT)
			{
				env->mouse->lmb = 1;
				trackball(env->mouse->prev_rot, 0.0, 0.0, 0.0, 0.0);		
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

void		cb_mouse_scroll(GLFWwindow *window, \
										double x_offset, \
										double y_offset)
{
	t_scop	*env;

	env = glfwGetWindowUserPointer(window);
	x_offset = 0.0f;
	if (env->world->cam_mod[0] >= 30.0f && env->world->cam_mod[0] <= 120.0f)
		env->world->cam_mod[0] -= y_offset;
	if (env->world->cam_mod[0] <= 30.0f)
		env->world->cam_mod[0] = 30.0f;
	if (env->world->cam_mod[0] >= 120.0f)
		env->world->cam_mod[0] = 120.0f;
}
