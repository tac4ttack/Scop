/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_log_gl_params.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:07:00 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/21 12:55:17 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void			scop_log_gl_params_print(const GLenum *params,
									const char **names)
{
	int				i;
	int				v;

	i = 0;
	scop_log("GL Context Params:\n");
	if (params && names)
	{
		while (i < 10)
		{
			v = 0;
			glGetIntegerv(params[i], &v);
			scop_log("%s %i\n", names[i], v);
			i++;
		}
	}
}

static void			scop_log_gl_params_other(const GLenum *params,
										const char **names)
{
	int				v[2];
	unsigned char	s;

	v[0] = 0;
	v[1] = 0;
	s = 0;
	if (params && names)
	{
		glGetIntegerv(params[10], v);
		scop_log("%s %i %i\n", names[10], v[0], v[1]);
		glGetBooleanv(params[11], &s);
		scop_log("%s %u\n", names[11], (unsigned int)s);
		scop_log("-----------------------------\n");
	}
}

void				scop_log_gl_params(void)
{
	const GLenum	params[] = {
		GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, GL_MAX_CUBE_MAP_TEXTURE_SIZE,
		GL_MAX_DRAW_BUFFERS, GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
		GL_MAX_TEXTURE_IMAGE_UNITS, GL_MAX_TEXTURE_SIZE, GL_MAX_VARYING_FLOATS,
		GL_MAX_VERTEX_ATTRIBS, GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
		GL_MAX_VERTEX_UNIFORM_COMPONENTS, GL_MAX_VIEWPORT_DIMS, GL_STEREO,
	};
	const char		*names[] = {
		"GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS", "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
		"GL_MAX_DRAW_BUFFERS", "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
		"GL_MAX_TEXTURE_IMAGE_UNITS", "GL_MAX_TEXTURE_SIZE",
		"GL_MAX_VARYING_FLOATS", "GL_MAX_VERTEX_ATTRIBS",
		"GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS", "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
		"GL_MAX_VIEWPORT_DIMS", "GL_STEREO",
	};

	scop_log_gl_params_print((const GLenum *)&params, &names[0]);
	scop_log_gl_params_other((const GLenum *)&params, &names[0]);
}
