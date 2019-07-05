/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_mouse_scroll.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 11:25:35 by fmessina          #+#    #+#             */
/*   Updated: 2019/07/01 11:25:55 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		cb_mouse_scroll(GLFWwindow *window, \
										double x_offset, \
										double y_offset)
{
	t_scop	*env;

	env = glfwGetWindowUserPointer(window);
	x_offset = 0.0f;
	if (env->world->cam_mod[0] >= 30.0f && env->world->cam_mod[0] <= 120.0f)
		env->world->cam_mod[0] -= y_offset;
	if (env->world->cam_mod[0] <= 30.0f)
		env->world->cam_mod[0] = 30.0f;
	if (env->world->cam_mod[0] >= 120.0f)
		env->world->cam_mod[0] = 120.0f;
}
