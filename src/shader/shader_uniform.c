/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_uniform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:12:40 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/08 17:37:03 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLuint	shader_uniform_update(t_scop *env)
{
	if (env)
	{
		glUniform1f(env->uni_time_id, env->uni_time_val);
		glUniformMatrix4fv(env->uni_model_id, 1, \
							GL_FALSE, &env->uni_model_val.m[0]);
		glUniformMatrix4fv(env->uni_view_id, 1, \
							GL_FALSE, &env->uni_view_val.m[0]);
		glUniformMatrix4fv(env->uni_projection_id, 1, \
							GL_FALSE, &env->uni_projection_val.m[0]);
		return (GL_TRUE);
	}
	return (GL_FALSE);
}

GLuint	shader_uniform_bind(t_scop *env)
{
	if (env)
	{
		env->uni_time_id = glGetUniformLocation(env->shader_program, "timeVal");
		env->uni_model_id = glGetUniformLocation(env->shader_program, "model");
		env->uni_view_id = glGetUniformLocation(env->shader_program, "view");
		env->uni_projection_id = glGetUniformLocation(env->shader_program, "projection");
		return (GL_TRUE);
	}
	return (GL_FALSE);
}
