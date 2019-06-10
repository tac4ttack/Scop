/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:37:49 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/12 10:37:56 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool glfw_clean(t_scop *env)
{
	if (env)
	{
		glDeleteVertexArrays(1, &env->vao);
		glDeleteBuffers(1, &env->vbo);
		glDeleteBuffers(1, &env->ebo);
		// add texture deletion
		// add shader deletion?
		// add shader uniform deletion?
		return (true);
	}
	return (error_bool("[ERROR glfw_clean]\tNULL Scop pointer!\n"));
}
