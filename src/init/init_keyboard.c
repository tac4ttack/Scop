/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_keyboard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:28:09 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/12 10:29:24 by fmessina         ###   ########.fr       */
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
		return (true);
	}
	return (error_bool("[ERROR init_key]\tNULL scop pointer!\n"));
}
