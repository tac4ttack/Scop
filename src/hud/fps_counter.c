/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:48:02 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/18 12:51:32 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

// unfinished

void			fps_counter(GLFWwindow *window)
{
	double		previous_seconds;
	double		current_seconds;
	double		elapsed_seconds;
	int			frame_count;

	previous_seconds = glfwGetTime();
	current_seconds = glfwGetTime();
	elapsed_seconds = current_seconds - previous_seconds;
	// fprintf(stdout, "prev = %f\ncur = %f\nelapse = %f\n", previous_seconds, current_seconds, elapsed_seconds);
	// if (elapsed_seconds > 0.25) // threshold too small? 0.00001
	if (elapsed_seconds > 0.25)
	{
		previous_seconds = current_seconds;
		double fps = (double)frame_count / elapsed_seconds;
		char tmp[128];
		sprintf(tmp, "opengl @ fps: %.2f", ((double)frame_count / elapsed_seconds));
		glfwSetWindowTitle(window, tmp);
		frame_count = 0;
	}
	frame_count++;
}
