/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 10:50:47 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/19 11:43:01 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool init_glew(void)
{
		// To improve support for newer OpenGL releases
		glewExperimental = GL_TRUE;
		// start GLEW extension handler
		if (glewInit() != GLEW_OK)
		{
			scop_log_err("Failed to initialize GLEW\n");
			return (error_bool("[ERROR init_glew()]\tGLEW init fail"));
		}
		glEnable(GL_DEPTH_TEST); // enable depth-testing
		glDepthFunc(GL_LESS);	// depth-testing interprets a smaller value as "closer"
		scop_log_gl_params();
		return (scop_log("Renderer: %s\n", glGetString(GL_RENDERER)) &
			scop_log("OpenGL version supported %s\n", glGetString(GL_VERSION)));
}

bool		init_glfw(t_scop *env)
{
	if (env)
	{
		if (!glfwInit())
			return (error("[ERROR init_glfw()]\t GLFW3 init fail"));
		if (MAC)
		{
			scop_log("You are on MacOSX!\n");// Required under MacOSX
			glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Will fetch the latest compatible version above 3.2 for post mavericks systems
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	// Pour rendre MacOS heureux, ne devrait pas être nécessaire mais il l'est
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL
		}
		if (!(env->win = glfwCreateWindow(WIDTH, HEIGHT, "Scop", NULL, NULL)))
		{
			scop_log_err("ERROR: could not open window with GLFW3\n");
			glfwTerminate();
			return (error("[ERROR init_glfw()]\tGLFW window creation fail"));
		}
		glfwMakeContextCurrent(env->win); // Attach window and context
		glfwSetWindowSizeCallback(env->win, gl_window_callback); // Set up a callback for windows events
		return (init_glew());
	}
	return (NULL);
}

t_scop		*init(const char *av)
{
	t_scop	*env;

	if (av)
	{
		if (!(env = ft_memalloc(sizeof(t_scop))))
			return (error("[ERROR init()]\tCould not allocate memory"));
		assert(scop_log_restart()); 		// start the GL logger
		scop_log("Starting GLFW\n%s\n", glfwGetVersionString());
		glfwSetErrorCallback(glfw_error_callback); // register the error call-back function that we wrote, above
		if (!(init_glfw(env)))
			return (error("[ERROR init()]\tCould initialize GLFW and GLEW"));
		return (env);
	}
	return (NULL);
}
