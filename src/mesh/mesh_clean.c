/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 12:21:33 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/06 14:26:14 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	mesh_clean(t_mesh *mesh)
{
	if (mesh)
	{
		scop_log("Cleaning mesh data...", NULL);
		// (mesh->object ? ft_memdel((void**)&mesh->object) : 0);
		// (mesh->group ? ft_memdel((void**)&mesh->group) : 0);
		// (mesh->mtllib ? ft_memdel((void**)&mesh->mtllib) : 0);
		// (mesh->usemtl ? ft_memdel((void**)&mesh->usemtl) : 0);
		(mesh->vertex ? ft_memdel((void**)&mesh->vertex) : 0);
		(mesh->face ? ft_memdel((void**)&mesh->face) : 0);
		(mesh->normal ? ft_memdel((void**)&mesh->normal) : 0);
		(mesh->texture ? ft_memdel((void**)&mesh->texture) : 0);
		(mesh->space ? ft_memdel((void**)&mesh->space) : 0);
		(mesh->face_format ? ft_memdel((void**)&mesh->face_format) : 0);
		(mesh->prepack_vao ? ft_memdel((void**)&mesh->prepack_vao) : 0);
		(mesh->prepack_ebo ? ft_memdel((void**)&mesh->prepack_ebo) : 0);
		(mesh ? ft_memdel((void**)&mesh) : 0);
	}
}
