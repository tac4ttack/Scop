/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_uniform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:12:40 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/27 14:40:11 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLuint	shader_uniform_update(t_scop *env)
{
	if (env)
	{
		glUniformMatrix4fv(env->uni->mvp_id, 1, \
							GL_FALSE, (GLfloat *)&env->world->mvp.m);
		glUniform1i(env->uni->shading_mode_id, env->smooth_shading);
		glUniform1i(env->uni->desaturate_id, env->desaturate);
		glUniform1i(env->uni->colorize_id, env->colorize);
		glUniform1i(env->uni->texture_doge_id, env->texture_default);
		glUniform1i(env->uni->texture_mesh_id, env->texture_mesh);
		glUniform1i(env->uni->uv_mode_id, env->mesh_uv);
		return (GL_TRUE);
	}
	return (GL_FALSE);
}

GLuint	shader_uniform_bind(t_scop *env)
{
	if (env)
	{
		env->uni->mvp_id = glGetUniformLocation(env->shader_program, "uMVP");
		env->uni->shading_mode_id = glGetUniformLocation(env->shader_program, \
														"uShading");
		env->uni->desaturate_id = glGetUniformLocation(env->shader_program, \
														"uDesaturate");
		env->uni->colorize_id = glGetUniformLocation(env->shader_program, \
														"uColorize");
		env->uni->texture_doge_id = glGetUniformLocation(env->shader_program, \
														"uTextureDefault");
		env->uni->texture_mesh_id = glGetUniformLocation(env->shader_program, \
														"uTextureMesh");
		env->uni->uv_mode_id = glGetUniformLocation(env->shader_program, \
														"uTextureUVMode");
		return (GL_TRUE);
	}
	return (GL_FALSE);
}
