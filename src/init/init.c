/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 10:50:47 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/12 10:32:38 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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
		if (!(init_glfw(env)) || !(init_glew(env)) || !(init_keyboard(env)) \
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
