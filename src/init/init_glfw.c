/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_glfw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:28:09 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/27 14:22:01 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		init_glfw(t_scop *env)
{
	if (env)
	{
		scop_log("Starting GLFW\n%s\n", glfwGetVersionString());
		env->win_res[0] = WIDTH;
		env->win_res[1] = HEIGHT;
		env->win_res[2] = env->win_res[0] / env->win_res[1];
		if (!glfwInit())
			return (error("[ERROR init_glfw]\tGLFW3 init fail!\n"));
		glfwSetErrorCallback(cb_error); // register the error call-back function that we wrote, above
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Will fetch the latest compatible version above 3.2 for post mavericks systems
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL
		if (MAC)
		{
			scop_log("You are on MacOSX!\n");// Required under MacOSX
			glfwWindowHint(GLFW_SAMPLES, ANTIALIASING); // Nx antialiasing
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	// Pour rendre MacOS heureux, ne devrait pas être nécessaire mais il l'est
		}
		if (!(env->win = glfwCreateWindow(env->win_res[0], env->win_res[1], "Scop", NULL, NULL)))
		{
			glfwTerminate();
			return (error_bool("[ERROR init_glfw]\t" \
			"GLFW3 window creation fail!\n"));
		}
		glfwMakeContextCurrent(env->win); // Attach window and context
		glfwSetWindowUserPointer(env->win, (void*)env); // makes our env ptr available
		glfwGetFramebufferSize(env->win, &env->win_res[0], &env->win_res[1]);

		glfwSetInputMode(env->win, GLFW_STICKY_KEYS, 1);
		// glfwSetInputMode(env->win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// settings up callbacks
		glfwSetWindowSizeCallback(env->win, cb_window_size);
		glfwSetFramebufferSizeCallback(env->win, cb_framebuffer_size);
		glfwSetKeyCallback(env->win, (void(*)(GLFWwindow *, int, int, int, int))cb_keyboard);
		glfwSetCursorPosCallback(env->win, cb_mouse_pos);
		glfwSetMouseButtonCallback(env->win, cb_mouse_btn);
		glfwSetScrollCallback(env->win, cb_mouse_scroll);

		glEnable(GL_PROGRAM_POINT_SIZE);

		return (true);
	}
	return (error_bool("[ERROR init_glfw]\tNULL scop pointer!\n"));
}
