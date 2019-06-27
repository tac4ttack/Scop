/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cycle_desaturate.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:41:26 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/27 16:10:35 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	input_cycle_desaturate(t_scop *env)
{	
	if (env)
	{
		if (env->desaturate == 3)
			env->desaturate = 0;
		else
			env->desaturate++;
	}
}