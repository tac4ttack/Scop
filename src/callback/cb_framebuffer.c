/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_framebuffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:33:27 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/17 12:00:27 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	update_viewport(t_scop *env, int width, int height)
{
	if (env)
	{
		if (width > height)
			glViewport(0, (height - width) / 2.0, \
						width, width);
		else
			glViewport((width - height) / 2.0, 0, \
						height, height);
	}
}

void cb_framebuffer_size(GLFWwindow* win, int width, int height)
{
    t_scop *env;

    env = NULL;
    if (win)
    {
        env = glfwGetWindowUserPointer(win);
   		update_viewport(env, width, height);
    }
}
