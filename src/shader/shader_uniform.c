/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_uniform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:12:40 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/07 19:31:38 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLuint	shader_uniform_update(t_scop *env)
{
	if (env)
	{
		glUniform1f(env->uni_time_id, env->uni_time_val);
		return (GL_TRUE);
	}
	return (GL_FALSE);
}

GLuint	shader_uniform_bind(t_scop *env)
{
	if (env)
	{
		env->uni_time_id = glGetUniformLocation(env->shader_program, "timeVal");
		env->uni_mat_tra_id = glGetUniformLocation(env->shader_program, "mTranslation");
		env->uni_mat_rot_id = glGetUniformLocation(env->shader_program, "mRotation");
		env->uni_mat_sca_id = glGetUniformLocation(env->shader_program, "mScale");

		return (GL_TRUE);
	}
	return (GL_FALSE);
}
