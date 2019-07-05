/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:37:49 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/27 18:27:45 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	glfw_clean(t_scop *env)
{
	if (env)
	{
		glDeleteVertexArrays(1, &env->vao);
		glDeleteBuffers(1, &env->vbo);
		glDeleteBuffers(1, &env->ebo);
		glDeleteProgram(env->shader_program);
		return (true);
	}
	return (error_bool("[ERROR glfw_clean]\tNULL Scop pointer!\n"));
}
