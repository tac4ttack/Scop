/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_window_callback.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 11:40:21 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/18 16:25:20 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	gl_window_callback(GLFWwindow *win, const int width, const int height)
{
	if (win)
		scop_log("Window size has changed!\n new width = " \
				"%d\nnew height = %d\n\n", width, height);
}
