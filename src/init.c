/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 10:50:47 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/10 17:36:01 by fmessina         ###   ########.fr       */
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
		glViewport(0, (env->win_res[1] - env->win_res[0]) / 2.0, \
					env->win_res[0], env->win_res[0]);

		glEnable(GL_DEPTH_TEST); // enable depth-testing
		glDepthFunc(GL_LESS);	// depth-testing interprets a smaller value as "closer"

		glDisable(GL_CULL_FACE);

		glEnable(GL_BLEND);
		// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

static bool	init_uni_matrix(t_scop *env)
{
	if (env)
	{
		if (!(env->uni = ft_memalloc(sizeof(t_uni))))
			return (error_bool("[ERROR init_uni_matrix]\tCan\'t " \
			"allocate memory for OpenGL uniforms!\n"));

		if (!(env->cam = ft_memalloc(sizeof(t_cam))))
			return (error_bool("[ERROR init_uni_matrix]\tCan\'t " \
			"allocate memory for camera!\n"));
		env->cam->cam_mod[0] = FOV;
		env->cam->cam_mod[1] = NEAR;
		env->cam->cam_mod[2] = FAR;
		env->cam->speed = 0.05f;

		env->cam->pos = vec3f(0.0f, 0.0f, 3.0f);
		env->cam->front = vec3f(0.0f, 0.0f, -1.0f);
		env->cam->up = vec3f(0.0f, 1.0f, 0.0f);

		if (!(env->mat = ft_memalloc(sizeof(t_mat))))
			return (error_bool("[ERROR init_uni_matrix]\tCan\'t " \
			"allocate memory for matrix!\n"));
		env->mat->translation = mat4_set_identity();
		env->mat->translation = mat4_mul(env->mat->translation, \
							mat4_set_translation(vec3f(-0.5, -0.5, -1.25)));

		env->mat->rotation = mat4_set_identity();
		env->mat->rotation = mat4_mul(env->mat->rotation, \
							mat4_set_rotation(42.0f, vec3f(1.0, 1.0, 0.0)));

		env->mat->scale = mat4_set_identity();

		env->mat->view = mat4_set_lookat(env->cam->pos, \
					vec3f_add(env->cam->pos, env->cam->front), env->cam->up);


		env->mat->projection = mat4_set(0.0);
		env->mat->projection = mat4_set_perspective(env->cam->cam_mod[0], \
				env->win_res[2], env->cam->cam_mod[1], env->cam->cam_mod[2]);
		return (true);
	}
	return (error_bool("[ERROR init_uni_matrix]\tNULL scop pointer!\n"));
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
		if (!(init_glfw(env)) || !(init_glew(env)) || !(init_uni_matrix(env)))
		{
			free(env);
			return (error("[ERROR init]\tCould initialize OpenGL!\n"));
		}
		scop_log("\nSCOP initialization done!\n");
		return (env);
	}
	return (NULL);
}
