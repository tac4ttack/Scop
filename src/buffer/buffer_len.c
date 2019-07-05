/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 12:50:20 by fmessina          #+#    #+#             */
/*   Updated: 2019/07/05 12:50:53 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

size_t	buffer_get_ebo_len(t_scop *env)
{
	size_t res;

	if (env && env->mesh->face && env->mesh->n_face[0] > 0)
		res = sizeof(GLint) * env->mesh->n_face[0] * 3;
	else
		res = sizeof(GLint) * env->mesh->n_vertex[0];
	return (res);
}

size_t	buffer_get_vao_len(t_scop *env)
{
	size_t res;

	if (env && env->mesh->face && env->mesh->n_face[0] > 0)
		res = sizeof(GLfloat) * env->mesh->n_face[0] * 3 * VAOLEN;
	else
		res = sizeof(GLfloat) * env->mesh->n_vertex[0] * VAOLEN;
	return (res);
}
