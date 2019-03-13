/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:49:59 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/13 16:23:51 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		mesh_scale(t_scop *env, int key)
{
	t_mat4	trans;

	trans = mat4_set_identity();
	if (env)
	{
		if (key == GLFW_KEY_KP_ADD)
			trans = mat4_set_scale(vec3f(1.1f, 1.1f, 1.1f));
		else if (key == GLFW_KEY_KP_SUBTRACT)
			trans = mat4_set_scale(vec3f(0.9f, 0.9f, 0.9f));
		env->world->mesh_scale = mat4_mul(env->world->mesh_scale, trans);
		return (true);
	}
	return (false);
}
