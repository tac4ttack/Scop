/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 10:50:47 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/11 18:43:51 by fmessina         ###   ########.fr       */
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

		glfwSetInputMode(env->win, GLFW_STICKY_KEYS, 1);
		// glfwSetInputMode(env->win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glfwSetWindowSizeCallback(env->win, glfw_window_size_callback); // Set up a callback for windows events
		glfwSetKeyCallback(env->win, glfw_key_callback);

		glfwSetCursorPosCallback(env->win, glfw_mouse_pos_callback);
		glfwSetMouseButtonCallback(env->win, glfw_mouse_button_callback);
		glfwSetScrollCallback(env->win, glfw_mouse_scroll_callback);

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

		// glEnable(GL_BLEND);
		// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		env->time_last = glfwGetTime();
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

static bool	init_matrix(t_scop *env)
{
	if (env)
	{
		if (!(env->mat = ft_memalloc(sizeof(t_matrix))))
			return (error_bool("[ERROR init_matrix]\tCan\'t " \
			"allocate memory for matrix!\n"));
		env->mat->translation = mat4_set_identity();
		env->mat->translation = mat4_mul(env->mat->translation, \
							mat4_set_translation(vec3f(-0.5, -0.5, -1.25)));
		env->mat->rotation = quat_2_mat4(quat_euler(0.0, 0.0, 0.0));
		env->mat->scale = mat4_set_identity();
		env->mat->view = mat4_set_lookat(env->cam->pos, env->cam->front, env->cam->up);
		env->mat->projection = mat4_set(0.0);
		env->mat->projection = mat4_set_perspective(env->cam->cam_mod[0], \
				env->win_res[2], env->cam->cam_mod[1], env->cam->cam_mod[2]);
		return (true);
	}
	return (error_bool("[ERROR init_matrix]\tNULL scop pointer!\n"));
}

static bool	init_cam(t_scop *env)
{
	if (env)
	{
		if (!(env->cam = ft_memalloc(sizeof(t_camera))))
			return (error_bool("[ERROR init_cam]\tCan\'t " \
			"allocate memory for camera!\n"));
		env->cam->cam_mod[0] = FOV;
		env->cam->cam_mod[1] = NEAR;
		env->cam->cam_mod[2] = FAR;
		env->cam->speed = 0.05f;
		env->cam->pos = vec3f(0.0f, 0.0f, 3.0f);
		env->cam->front = vec3f(0.0f, 0.0f, -1.0f);
		env->cam->up = vec3f(0.0f, 1.0f, 0.0f);
		return (true);
	}
	return (error_bool("[ERROR init_cam]\tNULL scop pointer!\n"));
}

static bool	init_uniforms(t_scop *env)
{
	if (env)
	{
		if (!(env->uni = ft_memalloc(sizeof(t_uni))))
			return (error_bool("[ERROR init_uniforms]\tCan\'t " \
			"allocate memory for OpenGL uniforms!\n"));
		return (true);
	}
	return (error_bool("[ERROR init_uniforms]\tNULL scop pointer!\n"));
}

static bool	init_key(t_scop *env)
{
	if (env)
	{
		if (!(env->key = ft_memalloc(sizeof(t_keyboard))))
			return (error_bool("[ERROR init_key]\tCould not allocate" \
			"memory for the keyboard support!\n"));
		return (true);
	}
	return (error_bool("[ERROR init_key]\tNULL scop pointer!\n"));
}

static bool	init_mouse(t_scop *env)
{
	if (env)
	{
		if (!(env->mouse = ft_memalloc(sizeof(t_mouse))))
			return (error_bool("[ERROR init_mouse]\tCould not allocate" \
			"memory for the mouse support!\n"));
		env->mouse->ready = false;
		env->mouse->sensitivity = 0.05f;
		env->mouse->last[0] = (double)env->win_res[0] / 2.0;
		env->mouse->last[1] = (double)env->win_res[1] / 2.0;

		// not working ?
		// glfwSetCursorPos(env->win, env->mouse->last[0], env->mouse->last[1]);
		// glfwSetCursorPos(env->win, 0.0, 0.0);
		return (true);
	}
	return (error_bool("[ERROR init_mouse]\tNULL scop pointer!\n"));
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
		env->win_title = ft_memalloc(sizeof(char) * 100);
		if (!(init_glfw(env)) || !(init_glew(env)) || !(init_key(env)) \
			|| !(init_mouse(env)) || !(init_uniforms(env)) || !(init_cam(env)) \
			|| !(init_matrix(env)) || !(init_textures(env)))
		{
			free(env);
			return (error("[ERROR init]\tCould initialize Scop!\n"));
		}
		scop_log("\nSCOP initialization done!\n");
		return (env);
	}
	return (NULL);
}
