/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_window_size_callback.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 11:40:21 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/20 12:49:37 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	glfw_window_size_callback(GLFWwindow *win, \
									const int width, \
									const int height)
{
	if (win)
	{
		glViewport(0, 0, width, height);
		if (DEBUG_SCOP)
		{
			// add a print of a glGet(GL_VIEWPORT, param)
			scop_log("\nWindow size has changed!\tnew width = " \
					"%d\tnew height = %d\n", width, height);
			fprintf(stdout, "\nWindow size has changed!\tnew width = " \
					"%d\tnew height = %d\n", width, height);
		}
	}
}
