/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_uniforms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:28:09 by fmessina          #+#    #+#             */
/*   Updated: 2019/07/02 11:03:41 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	init_uniforms(t_scop *env)
{
	if (env)
	{
		if (!(env->uni = ft_memalloc(sizeof(t_uni))))
			return (error_bool("[ERROR init_uniforms]\tCan\'t " \
			"allocate memory for OpenGL uniforms!\n"));
		return (true);
	}
	return (error_bool("[ERROR init_uniforms]\tNULL Scop pointer!\n"));
}
