/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 10:50:47 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/25 10:37:55 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool		init_glfw(t_scop *env)
{
	if (env)
	{
		if (!glfwInit())
			return (error("[ERROR init_glfw()]\tGLFW3 init fail\n"));
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Will fetch the latest compatible version above 3.2 for post mavericks systems
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL
		if (MAC)
		{
			scop_log("You are on MacOSX!\n");// Required under MacOSX
			glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	// Pour rendre MacOS heureux, ne devrait pas être nécessaire mais il l'est
		}
		if (!(env->win = glfwCreateWindow(WIDTH, HEIGHT, "Scop", NULL, NULL)))
		{
			glfwTerminate();
			return (error_bool("[ERROR init_glfw()]\t" \
			"GLFW3 window creation fail\n"));
		}
		glfwMakeContextCurrent(env->win); // Attach window and context
		glfwSetWindowSizeCallback(env->win, glfw_window_size_callback); // Set up a callback for windows events
		return (true);
	}
	return (false);
}

static bool init_glew(void)
{
		glewExperimental = GL_TRUE; // To improve support for newer OpenGL releases
		if (glewInit() != GLEW_OK)	// start GLEW extension handler
			return (error_bool("[ERROR init_glew()]\t" \
			"Failed to initialize GLEW\n"));
		glViewport(0, 0, WIDTH, HEIGHT);
		glEnable(GL_DEPTH_TEST); // enable depth-testing
		glDepthFunc(GL_LESS);	// depth-testing interprets a smaller value as "closer"
		scop_log("Current system parameters are:\n");
		scop_log_gl_params();
		return (scop_log("Renderer: %s\n", glGetString(GL_RENDERER)) &
			scop_log("OpenGL version supported %s\n", glGetString(GL_VERSION)));
}

t_scop		*init(const char *av)
{
	t_scop	*env;

	if (av)
	{
		scop_log("\nSCOP initializing...\n");
		if (!(env = ft_memalloc(sizeof(t_scop))))
			return (error("[ERROR init()]\tCould not allocate memory"));
		assert(scop_log_restart());		// start the GL logger
		scop_log("Starting GLFW\n%s\n", glfwGetVersionString());
		glfwSetErrorCallback(glfw_error_callback); // register the error call-back function that we wrote, above
		if (!(init_glfw(env)))
		{
			free(env);
			return (error("[ERROR init()]\tCould initialize GLFW"));
		}
		if (!(init_glew()))
		{
			free(env);
			return (error("[ERROR init()]\tCould initialize GLEW"));
		}
		scop_log("\nSCOP initialization done!\n");
		return (env);
	}
	return (NULL);
}
