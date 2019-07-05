/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:49:59 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/27 13:19:51 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	mesh_rotate_self(t_scop *env)
{
	if (env)
	{
		if (env->key->key_i)
			env->world->mesh_orient = quat_mul(env->world->mesh_orient, \
										quat_rot(vec3f(1.0, 0.0, 0.0), 1.0));
		if (env->key->key_k)
			env->world->mesh_orient = quat_mul(env->world->mesh_orient, \
										quat_rot(vec3f(1.0, 0.0, 0.0), -1.0));
		if (env->key->key_j)
			env->world->mesh_orient = quat_mul(env->world->mesh_orient, \
										quat_rot(vec3f(0.0, 1.0, 0.0), 1.0));
		if (env->key->key_l)
			env->world->mesh_orient = quat_mul(env->world->mesh_orient, \
										quat_rot(vec3f(0.0, 1.0, 0.0), -1.0));
		if (env->key->key_u)
			env->world->mesh_orient = quat_mul(env->world->mesh_orient, \
										quat_rot(vec3f(0.0, 0.0, 1.0), 1.0));
		if (env->key->key_o)
			env->world->mesh_orient = quat_mul(env->world->mesh_orient, \
										quat_rot(vec3f(0.0, 0.0, 1.0), -1.0));
		return (true);
	}
	return (error_bool("[ERROR mesh_rotate_self]\tNULL Scop pointer!\n"));
}
