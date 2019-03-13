/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:28:09 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/13 13:44:23 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	init_matrix(t_scop *env)
{
	if (env)
	{
		if (!(env->mat = ft_memalloc(sizeof(t_matrix))))
			return (error_bool("[ERROR init_matrix]\tCan\'t " \
			"allocate memory for matrix!\n"));
		env->mat->translation = mat4_set_identity();
		// env->mat->translation = mat4_mul(env->mat->translation, \
							// mat4_set_translation(vec3f(-0.5, -0.5, -1.25)));
		env->mat->mesh_euler[0] = 45.0;
		env->mat->mesh_euler[1] = 45.0;
		env->mat->mesh_euler[2] = 0.0;
		env->mat->rotation = mat4_set_identity();
		env->mat->rotation = quat_2_mat4(quat_euler(env->mat->mesh_euler[0], \
							env->mat->mesh_euler[1], env->mat->mesh_euler[2]));
		env->mat->scale = mat4_set_identity();
		env->mat->view = cam_get_lookat(env->cam);
		env->mat->projection = mat4_set(0.0);
		env->mat->projection = mat4_set_perspective(env->cam->cam_mod[0], \
				env->win_res[2], env->cam->cam_mod[1], env->cam->cam_mod[2]);
		return (true);
	}
	return (error_bool("[ERROR init_matrix]\tNULL scop pointer!\n"));
}
