/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 10:50:47 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/08 18:27:40 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool		init_glfw(t_scop *env)
{
	if (env)
	{
		scop_log("Starting GLFW\n%s\n", glfwGetVersionString());
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
		if (!(env->win = glfwCreateWindow(WIDTH, HEIGHT, "Scop", NULL, NULL)))
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

static bool init_glew(void)
{
		glewExperimental = GL_TRUE; // To improve support for newer OpenGL releases
		if (glewInit() != GLEW_OK)	// start GLEW extension handler
			return (error_bool("[ERROR init_glew\t" \
			"Failed to initialize GLEW!\n"));
		glViewport(0, 0, WIDTH, HEIGHT);
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
		mat4_set_identity(&env->uni_model_val);
		// rotate sightly
		mat_rotate(&env->uni_model_val, 10, 'x');
		mat_rotate(&env->uni_model_val, 35, 'y');

		mat4_set_identity(&env->uni_view_val);
		// put the camera sightly in the back
		mat_translate(&env->uni_view_val, vec3f(0.0f, 0.0f, -3.0f));

		// lr tb nf
		float r, l, t, b, n, f;
		l = 0.0f;
		r = WIDTH;
		b = 0.0f;
		t = HEIGHT;
		n = NEAR;
		f = FAR;

		mat4_set(&env->uni_projection_val, 0.0);
		env->uni_projection_val.m[0] = 2.0f / (r - l);
		env->uni_projection_val.m[5] = 2.0f / (t - b);
		env->uni_projection_val.m[10] = -2.0f / (f -n);
		env->uni_projection_val.m[12] = -(r + l) / (r - l);
		env->uni_projection_val.m[13] = -(t + b) / (t - b);
		env->uni_projection_val.m[14] = -(f + n) / (f - n);
		env->uni_projection_val.m[15] = 1.0f;
		// env->uni_projection_val.m[0] = (2.0 / r-l);
		// env->uni_projection_val.m[3] = -(r+l / r-l);
		// env->uni_projection_val.m[5] = (2.0 / t-b);
		// env->uni_projection_val.m[7] = -(b+t / t-b);
		// env->uni_projection_val.m[10] = (-2.0 / f-n);
		// env->uni_projection_val.m[11] = -(f+n / f-n);
		// env->uni_projection_val.m[15] = 1.0;

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
		if (!(init_glew()))
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
