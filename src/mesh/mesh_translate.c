/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_translate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:49:59 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/12 10:50:47 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		mesh_translate(t_scop *env, int key)
{
	t_mat4	trans;

	trans = mat4_set_identity();
	if (env)
	{
		if (key == GLFW_KEY_KP_8)
			trans = mat4_set_translation(vec3f(0.0, 0.1, 0.0));
		else if (key == GLFW_KEY_KP_5)
			trans = mat4_set_translation(vec3f(0.0, -0.1, 0.0));
		else if (key == GLFW_KEY_KP_4)
			trans = mat4_set_translation(vec3f(-0.1, 0.00, 0.0));
		else if (key == GLFW_KEY_KP_6)
			trans = mat4_set_translation(vec3f(0.1, 0.00, 0.0));
		else if (key == GLFW_KEY_KP_9)
			trans = mat4_set_translation(vec3f(0.0, 0.00, -0.1));
		else if (key == GLFW_KEY_KP_7)
			trans = mat4_set_translation(vec3f(0.0, 0.00, 0.1));
		env->mat->translation = mat4_mul(env->mat->translation, trans);
		return (true);
	}
	return (false);
}
