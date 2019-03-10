/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_uniform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:12:40 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/10 13:19:19 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLuint	shader_uniform_update(t_scop *env)
{
	if (env)
	{
		glUniform1f(env->uni->time_id, env->uni->time);
		glUniformMatrix4fv(env->uni->translation_id, 1, \
							GL_TRUE, &env->mat->translation.m[0]);
		glUniformMatrix4fv(env->uni->rotation_id, 1, \
							GL_TRUE, &env->mat->rotation.m[0]);
		glUniformMatrix4fv(env->uni->scale_id, 1, \
							GL_TRUE, &env->mat->scale.m[0]);
		glUniformMatrix4fv(env->uni->view_id, 1, \
							GL_FALSE, &env->mat->view.m[0]);
		glUniformMatrix4fv(env->uni->projection_id, 1, \
							GL_FALSE, &env->mat->projection.m[0]);
		return (GL_TRUE);
	}
	return (GL_FALSE);
}

GLuint	shader_uniform_bind(t_scop *env)
{
	if (env)
	{
		env->uni->time_id = glGetUniformLocation(env->shader_program, \
												"timeVal");
		env->uni->translation_id = glGetUniformLocation(env->shader_program, \
												"translation");
		env->uni->rotation_id = glGetUniformLocation(env->shader_program, \
												"rotation");
		env->uni->scale_id = glGetUniformLocation(env->shader_program, \
												"scale");
		env->uni->view_id = glGetUniformLocation(env->shader_program, "view");
		env->uni->projection_id = glGetUniformLocation(env->shader_program, \
												"projection");
		return (GL_TRUE);
	}
	return (GL_FALSE);
}
