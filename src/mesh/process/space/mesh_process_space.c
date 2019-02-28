/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_process_space.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:02:16 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/28 17:58:13 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool		create_vp_array(t_mesh *mesh)
{
	if (mesh)
	{
		if (!(mesh->space = ft_memalloc(sizeof(float) \
											* 3 * mesh->n_space[0])))
			return (error_bool("[ERROR create_vp_array]\t" \
			"Mesh vertex space parameter array memory allocation failed!\n"));
		return (true);
	}
	return (error_bool("[ERROR create_vp_array]\t" \
	"NULL mesh pointer!\n"));
}

bool			mesh_process_space(t_mesh *mesh, char *str)
{
	size_t		i[2];

	if (mesh && str)
	{
		if (!mesh->space && mesh->n_space > 0)
			if (!create_vp_array(mesh))
				return (error_bool("[ERROR mesh_process_space]\t" \
				"Mesh vertex space parameter array creation failed!\n"));
		i[0] = (++mesh->n_space[1] - 1) * 3;
		i[1] = sscanf(str, "vp %f %f %f\n", &mesh->space[i[0]], \
					&mesh->space[i[0] + 1], &mesh->space[i[0]] + 2);
		if (i[1] < 1)
			return (error_bool("[ERROR mesh_process_space]\t" \
			"Wrong vertex space paremeter definition line!\n"));
		return (true);
	}
	return (error_bool("[ERROR mesh_process_space]\t" \
	"NULL mesh or string pointer!\n"));
}
