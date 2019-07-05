/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:28:09 by fmessina          #+#    #+#             */
/*   Updated: 2019/07/02 11:03:41 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	init_mouse(t_scop *env)
{
	if (env)
	{
		if (!(env->mouse = ft_memalloc(sizeof(t_mouse))))
			return (error_bool("[ERROR init_mouse]\tCould not allocate" \
			"memory for the mouse support!\n"));
		env->mouse->ready = false;
		env->mouse->rot_speed = 1.0f;
		env->mouse->tra_speed = 4.0f;
		env->mouse->last[0] = (double)env->win_res[0] / 2.0;
		env->mouse->last[1] = (double)env->win_res[1] / 2.0;
		return (true);
	}
	return (error_bool("[ERROR init_mouse]\tNULL Scop pointer!\n"));
}
