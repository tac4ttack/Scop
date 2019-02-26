/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_uniform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:12:40 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/26 12:27:09 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLuint	shader_uniform_update(t_scop *env)
{
	if (env)
	{
		glUniform1f(env->uni_time_id, env->uni_time_val);

		// glUniform4f(env->uniform_test, 0.0f, (sin(env->time_value) / 2.0f) + 0.5f, 0.0f, 1.0f);
		return (GL_TRUE);
	}
	return (GL_FALSE);
}

GLuint	shader_uniform_bind(t_scop *env)
{
	if (env)
	{
		env->uni_time_id = glGetUniformLocation(env->shader_program, "timeVal");

		// env->uniform_test = glGetUniformLocation(env->shader_program, "ourColor");
		return (GL_TRUE);
	}
	return (GL_FALSE);
}
