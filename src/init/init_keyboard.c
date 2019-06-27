/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_keyboard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:28:09 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/27 15:18:39 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	init_keyboard(t_scop *env)
{
	if (env)
	{
		if (!(env->key = ft_memalloc(sizeof(t_keyboard))))
			return (error_bool("[ERROR init_key]\tCould not allocate" \
			"memory for the keyboard support!\n"));
		env->auto_rot = true;
		env->auto_rot_speed = 1.0f;
		env->mesh_uv = true;
		return (true);
	}
	return (error_bool("[ERROR init_key]\tNULL scop pointer!\n"));
}
