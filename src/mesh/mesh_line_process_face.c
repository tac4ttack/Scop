/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_line_process_face.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 12:59:37 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/21 18:03:59 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool create_face_array(t_mesh *mesh)
{
	short int size;

	if (mesh)
	{
		(size = mesh->n_face_mod == 3 ? 2 : mesh->n_face_mod + 1);
		if (!(mesh->face = ft_memalloc(sizeof(int) * mesh->n_face_vertices * 3)))
			return (error_bool("[ERROR create_face_array()]\t" \
			"Mesh face array memory allocation failed"));
		mesh->n_face = 1;
		return (true);
	}
	return (false);
}

// static bool	extend_face_array(t_mesh *src)
// {
// 	int		*new;

// 	if (src)
// 	{
// 		if (!(new = ft_memalloc(sizeof(int) \
// 					* (src->n_face + 1) * src->n_face_vertices * 3)))
// 			return (error_bool("[ERROR extend_face_array()]\t" \
// 			"New mesh face array memory allocation failed"));
// 		if (!(new = ft_memcpy(new, src->face, (sizeof(int) \
// 					* (src->n_face) * src->n_face_vertices))))
// 			return (error_bool("[ERROR extend_face_array()]\t" \
// 			"Old mesh face array data copy to new array failed"));
// 		src->n_face++;
// 		free(src->face);
// 		src->face = new;
// 		return (true);
// 	}
// 	return (false);
// }



bool			mesh_line_process_face(t_mesh *mesh, char *str)
{
	if (mesh && str)
	{
		if (!mesh->face && mesh->n_face == 0) //
		{
			if (!(mesh_get_face_type(mesh, str)))
				return (error_bool("[ERROR mesh_line_process_face()]\t" \
				"Mesh face line parsing & analysis failed"));
			if (!create_face_array(mesh))
				return (error_bool("[ERROR mesh_line_process_face()]\t" \
				"Mesh face array creation failed"));
		}
		// else
		// {
		// 	if (!extend_face_array(mesh))
		// 		return (error_bool("[ERROR mesh_line_process_face()]\t" \
		// 		"Mesh face array extension failed"));
		// }
		// if (!(mesh_extract_face_data(mesh, ft_strsplit(str, ' '))))
		// 	return (error_bool("[ERROR mesh_line_process_face()]\t" \
		// 		"Mesh face line analysis failed"));
		return (true);
	}
	return (false);
}
