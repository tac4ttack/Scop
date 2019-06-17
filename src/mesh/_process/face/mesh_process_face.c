/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_process_face.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 12:59:37 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/06 11:04:00 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool	create_face_array(t_mesh *mesh)
{
	if (mesh)
	{
		if (!(mesh->face = ft_memalloc(sizeof(GLint) * mesh->n_face[0] * 9)))
			return (error_bool("[ERROR create_face_array]\t" \
			"Mesh face array memory allocation failed!\n"));
		return (true);
	}
	return (false);
}

bool		mesh_process_face(t_mesh *mesh, char *str)
{
	int		i[2];
	char	**split;

	if (mesh && str && !(i[1] = 0))
	{
		if (!mesh->face && mesh->n_face[0] > 0)
			if (!create_face_array(mesh))
				return (error_bool("[ERROR mesh_line_process_face]\t" \
				"Mesh face array creation failed!\n"));
		i[0] = (++mesh->n_face[1] - 1) * 9;
		if (!(split = ft_strsplit(str, ' ')))
			return (error_bool("[ERROR mesh_line_process_face]\t" \
			"Mesh could not split face line for processing its data!\n"));
		if (split_len(split) == 5)
			i[1] = !mesh_process_face_quad(mesh, split + 1, i[0]);
		else
			i[1] = !mesh_process_face_triangle(mesh, split + 1, i[0]);
		split_destroy(split);
		if (i[1])
			return (error_bool("[ERROR mesh_line_process_face]\t"\
			"Failed to process face element definition line!\n"));
		return (true);
	}
	return (error_bool("[ERROR mesh_line_process_face]\t" \
	"NULL mesh or line pointer!\n"));
}
