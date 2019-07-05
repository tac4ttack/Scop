/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 10:38:15 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/27 17:41:30 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	input_process(t_scop *env)
{
	if (env && env->key)
	{
		if (env->key->key_autorot_minus)
			env->auto_rot_speed -= 0.01;
		if (env->key->key_autorot_plus)
			env->auto_rot_speed += 0.01;
		if (env->key->key_q || env->key->key_w || env->key->key_e \
				|| env->key->key_a || env->key->key_s || env->key->key_d)
			mesh_translate(env);
		if (env->key->key_u || env->key->key_i || env->key->key_o \
				|| env->key->key_j || env->key->key_k || env->key->key_l)
			mesh_rotate_self(env);
		if (env->key->key_lbra || env->key->key_rbra)
			mesh_scale(env);
		return (true);
	}
	return (error_bool("[ERROR input_process]\tNULL Scop pointer!\n"));
}
