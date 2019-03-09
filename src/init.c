/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 10:50:47 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/09 16:41:57 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool		init_glfw(t_scop *env)
{
	if (env)
	{
		scop_log("Starting GLFW\n%s\n", glfwGetVersionString());
		env->win_res[0] = WIDTH;
		env->win_res[1] = HEIGHT;
		env->win_res[2] = env->win_res[0] / env->win_res[1];
		if (!glfwInit())
			return (error("[ERROR init_glfw]\tGLFW3 init fail!\n"));
		glfwSetErrorCallback(glfw_error_callback); // register the error call-back function that we wrote, above
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
		// glfwSetInputMode(env->win, GLFW_STICKY_KEYS, 1);
		glfwSetWindowSizeCallback(env->win, glfw_window_size_callback); // Set up a callback for windows events
		glfwSetKeyCallback(env->win, glfw_key_callback);

		return (true);
	}
	return (error_bool("[ERROR init_glfw]\tNULL scop pointer!\n"));
}

static bool init_glew(t_scop *env)
{
		glewExperimental = GL_TRUE; // To improve support for newer OpenGL releases
		if (glewInit() != GLEW_OK)	// start GLEW extension handler
			return (error_bool("[ERROR init_glew\t" \
			"Failed to initialize GLEW!\n"));
		glViewport(0, 0, env->win_res[0], env->win_res[1]);
		glEnable(GL_DEPTH_TEST); // enable depth-testing
		glDepthFunc(GL_LESS);	// depth-testing interprets a smaller value as "closer"
		scop_log("Current system parameters are:\n");
		scop_log_gl_params();
		return (scop_log("Renderer: %s\n", glGetString(GL_RENDERER)) &
			scop_log("OpenGL version supported %s\n", glGetString(GL_VERSION)));
}

static bool	init_textures(t_scop *env)
{
	if (env)
	{
		if (!(env->texture = ft_memalloc(sizeof(t_texture))))
			return (error_bool("[ERROR init_textures]\t" \
			"Can\'t allocate memory for textures!\n"));
		if (!(env->texture->pixels = tga_load_file(DEFAULT_TEXTURE, \
												&env->texture[0].size[0], \
												&env->texture[0].size[1])))
			return (error_bool("[ERROR init_textures]\t" \
			"Could not load the default Doge texture!\n"));
		env->n_texture = 1;
		return (true);
	}
	return (error_bool("[ERROR init_textures]\tNULL scop pointer!\n"));
}

void		debug_init_matrix(t_scop *env)
{
	if (env)
	{
		env->uni_model_val = mat4_set_identity();
		env->uni_model_val = mat4_mul(env->uni_model_val, \
		 					mat4_set_translation(vec3f(-0.5f, -0.5f, -1.5f)));


		env->uni_view_val = mat4_set_identity();
		// put the camera sightly in the back
		env->uni_view_val = mat4_mul(env->uni_view_val, \
							mat4_set_translation(vec3f(0.0f, 0.0f, -3.0f)));

		env->uni_projection_val = mat4_set(0.0);
		env->uni_projection_val = mat4_set_perspective(FOV, env->win_res[2], NEAR, FAR);
	}
}


t_scop		*init(const char *av)
{
	t_scop	*env;

	if (av)
	{
		assert(scop_log_restart());
		scop_log("\nSCOP initializing...\n");
		if (!(env = ft_memalloc(sizeof(t_scop))))
			return (error("[ERROR init]\t" \
			"Can\'t allocate memory for Scop!\n"));
		if (!init_textures(env))
			return (error("[ERROR init]\t" \
			"Could not initialize Scop default Doge texture!\n"));
		if (!(init_glfw(env)))
		{
			free(env);
			return (error("[ERROR init]\tCould initialize GLFW!\n"));
		}
		if (!(init_glew(env)))
		{
			free(env);
			return (error("[ERROR init]\tCould initialize GLEW!\n"));
		}
		scop_log("\nSCOP initialization done!\n");


		// DEBUG MATRIX TESTING
		debug_init_matrix(env);
		return (env);
	}
	return (NULL);
}
