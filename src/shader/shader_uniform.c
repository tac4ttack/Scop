/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_uniform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:12:40 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/08 13:32:33 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLuint	shader_uniform_update(t_scop *env)
{
	if (env)
	{
		glUniform1f(env->uni_time_id, env->uni_time_val);
		glUniformMatrix4fv(env->uni_transform_id, 1, \
							GL_FALSE, &env->uni_transform_val.m[0]);
		return (GL_TRUE);
	}
	return (GL_FALSE);
}

GLuint	shader_uniform_bind(t_scop *env)
{
	if (env)
	{
		env->uni_time_id = glGetUniformLocation(env->shader_program, \
												"timeVal");
		env->uni_transform_id = glGetUniformLocation(env->shader_program, \
													"mTransformation");
		return (GL_TRUE);
	}
	return (GL_FALSE);
}
