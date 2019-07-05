/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 10:50:47 by fmessina          #+#    #+#             */
/*   Updated: 2019/07/05 12:38:58 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool	init_options(t_scop *env)
{
	if (env)
	{
		env->auto_rot = true;
		env->auto_rot_speed = DEFAULT_MESH_AUTOROT_SPEED;
		env->mesh_uv = true;
		env->vsync = true;
		return (true);
	}
	return (error_bool("[ERROR init_options]\tNULL Scop pointer!\n"));
}

t_scop		*init(const char *av)
{
	t_scop	*env;

	if (av)
	{
		srand((unsigned int)time(NULL));
		assert(scop_log_restart());
		scop_log("\nSCOP initializing...\n");
		if (!(env = ft_memalloc(sizeof(t_scop))))
			return (error("[ERROR init]\t" \
			"Can\'t allocate memory for Scop!\n"));
		env->win_title = ft_memalloc(sizeof(char) * 100);
		if (!(init_glfw(env)) || !(init_glew(env)) || !(init_keyboard(env)) \
			|| !(init_mouse(env)) || !(init_uniforms(env)) \
			|| !(init_world(env)) || !(init_textures(env)) \
			|| !(init_options(env)))
		{
			free(env);
			return (error("[ERROR init]\tCould initialize Scop!\n"));
		}
		scop_log("\nSCOP initialization done!\n\n");
		return (env);
	}
	return (NULL);
}
