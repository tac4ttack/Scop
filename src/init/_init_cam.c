/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:28:09 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/13 14:03:42 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	init_cam(t_scop *env)
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
		env->cam->up = vec3f(0.0f, 1.0f, 0.0f);
		env->cam->front = vec3f(0.0f, 0.0f, -1.0f);
		env->cam->world_up = env->cam->up;
		return (true);
	}
	return (error_bool("[ERROR init_cam]\tNULL scop pointer!\n"));
}
