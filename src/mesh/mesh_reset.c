/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_reset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:27:54 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/27 13:28:37 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	mesh_reset(t_scop *env)
{
	if (env)
	{
		env->world->mesh_orient = quat_set_identity();
		env->world->mesh_position = vec3f(0, 0, 0);
		env->world->mesh_scaler = vec3f(1, 1, 1);
	}
}