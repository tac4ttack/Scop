/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_uniform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:12:40 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/14 13:38:35 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLuint	shader_uniform_update(t_scop *env)
{
	if (env)
	{
		glUniformMatrix4fv(env->uni->mvp_id, 1, \
							GL_FALSE, (GLfloat *)&env->world->mvp.m);
		return (GL_TRUE);
	}
	return (GL_FALSE);
}

GLuint	shader_uniform_bind(t_scop *env)
{
	if (env)
	{
		env->uni->mvp_id = glGetUniformLocation(env->shader_program, "mvp");
		return (GL_TRUE);
	}
	return (GL_FALSE);
}
