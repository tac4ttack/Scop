/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_glfw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:28:09 by fmessina          #+#    #+#             */
/*   Updated: 2019/07/02 11:03:41 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	init_glfw_callbacks(t_scop *env)
{
	if (env)
	{
		glfwSetWindowSizeCallback(env->win, cb_window_size);
		glfwSetFramebufferSizeCallback(env->win, cb_framebuffer_size);
		glfwSetKeyCallback(env->win, \
						(void(*)(GLFWwindow *, int, int, int, int))cb_keyboard);
		glfwSetCursorPosCallback(env->win, cb_mouse_pos);
		glfwSetMouseButtonCallback(env->win, cb_mouse_btn);
		glfwSetScrollCallback(env->win, cb_mouse_scroll);
	}
}

static bool	init_glfw_window(t_scop *env)
{
	if (env)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		if (MAC)
		{
			scop_log("You are on MacOSX!\n");
			glfwWindowHint(GLFW_SAMPLES, ANTIALIASING);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		}
		if (!(env->win = glfwCreateWindow(env->win_res[0], \
										env->win_res[1], \
										"Scop", \
										NULL, \
										NULL)))
		{
			glfwTerminate();
			return (error_bool("[ERROR init_glfw_window]\t" \
			"GLFW3 window creation fail!\n"));
		}
		return (true);
	}
	return (error_bool("[ERROR init_glfw]\tNULL Scop pointer!\n"));
}

bool		init_glfw(t_scop *env)
{
	if (env)
	{
		scop_log("Starting GLFW\n%s\n", glfwGetVersionString());
		env->win_res[0] = WIDTH;
		env->win_res[1] = HEIGHT;
		env->win_res[2] = env->win_res[0] / env->win_res[1];
		if (!glfwInit())
			return (error_bool("[ERROR init_glfw]\tGLFW3 init fail!\n"));
		glfwSetErrorCallback(cb_error);
		if (!(init_glfw_window(env)))
			return (false);
		glfwMakeContextCurrent(env->win);
		glfwSetWindowUserPointer(env->win, (void*)env);
		glfwGetFramebufferSize(env->win, &env->win_res[0], &env->win_res[1]);
		glfwSetInputMode(env->win, GLFW_STICKY_KEYS, 1);
		init_glfw_callbacks(env);
		glEnable(GL_PROGRAM_POINT_SIZE);
		return (true);
	}
	return (error_bool("[ERROR init_glfw]\tNULL Scop pointer!\n"));
}
