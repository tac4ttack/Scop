/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_translate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:49:59 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/27 13:19:27 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		mesh_translate(t_scop *env)
{
	if (env)
	{	
		if (env->key->key_w)
			env->world->mesh_position = vec3f_add(env->world->mesh_position, \
												vec3f(0.0, 0.1, 0.0));
		if (env->key->key_s)
			env->world->mesh_position = vec3f_add(env->world->mesh_position, \
												vec3f(0.0, -0.1, 0.0));
		if (env->key->key_a)
			env->world->mesh_position = vec3f_add(env->world->mesh_position, \
												vec3f(-0.1, 0.00, 0.0));
		if (env->key->key_d)
			env->world->mesh_position = vec3f_add(env->world->mesh_position, \
												vec3f(0.1, 0.00, 0.0));
		if (env->key->key_q)
			env->world->mesh_position = vec3f_add(env->world->mesh_position, \
												vec3f(0.0, 0.00, -0.1));
		if (env->key->key_e)
			env->world->mesh_position = vec3f_add(env->world->mesh_position, \
												vec3f(0.0, 0.00, 0.1));
		return (true);
	}
	return (error_bool("[ERROR mesh_translate]\tNULL Scop pointer!\n"));
}
