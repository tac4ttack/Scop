/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_uniform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:12:40 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/20 11:15:54 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLuint	shader_uniform_update(t_scop *env)
{
	if (env)
	{
		// glUniformMatrix4fv(env->shader.mvploc, 1, GL_FALSE, env->sim.mvp.m);
		// glUniform1i(env->shader.smdloc, env->mod.shading);
		glUniform1i(env->uniform_test, env->uniform_test_value);
		return (GL_TRUE);
	}
	return (GL_FALSE);
}

GLuint	shader_uniform_bind(t_scop *env)
{
	if (env)
	{
		env->uniform_test = glGetUniformLocation(env->shader_program, "uniform_test");
		return (GL_TRUE);
	}
	return (GL_FALSE);
}
