/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_pack_vao_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:33:55 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/27 18:51:49 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool mesh_pack_vao_data(t_mesh *mesh)
{
	if (mesh)
	{
		return (true);
	}
	return (error_bool("[ERROR mesh_pack_vao_data]\tNULL mesh pointer!\n"));
}
