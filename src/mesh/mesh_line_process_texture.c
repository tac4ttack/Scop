/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_line_process_texture.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:56:15 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/27 12:41:51 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool	create_texture_array(t_mesh *mesh)
{
	if (mesh)
	{
		if (!(mesh->texture = ft_memalloc(sizeof(float) * 3 * mesh->n_texture[0])))
			return (error_bool("[ERROR create_texture_array]\t" \
			"Mesh texture coordinates array memory allocation failed!\n"));
		return (true);
	}
	return ((error_bool("[ERROR create_texture_array]\t" \
	"NULL mesh pointer!\n")));
}

bool		mesh_line_process_texture(t_mesh *mesh, char *str)
{
	int		i[2];

	if (mesh && str)
	{
		if (!mesh->texture && mesh->n_texture[0] > 0)
			if (!create_texture_array(mesh))
				return (error_bool("[ERROR mesh_line_process_texture]\t" \
				"Mesh texture array creation failed!\n"));
		i[0] = (++mesh->n_texture[1] - 1) * 3;
		i[1] = sscanf(str, "vt %f %f %f\n",	&mesh->texture[i[0]], \
					&mesh->texture[i[0] + 1], &mesh->texture[i[0] + 2]);
		if (i[1] == 0 || i[1] > 3)
			return (error_bool("[ERROR mesh_line_process_texture]\t" \
			"Texture coordinate line format is invalid!\n"));
		return (true);
	}
	return (false);
}
