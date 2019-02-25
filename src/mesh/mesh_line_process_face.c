/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_line_process_face.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 12:59:37 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/25 12:48:16 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

 bool	create_face_array(t_mesh *mesh)
{
	if (mesh)
	{
		if (!(mesh->face = ft_memalloc(sizeof(int) \
										* mesh->n_face[4] \
										* mesh->n_face[2] \
										* mesh->n_face[0])))
			return (error_bool("[ERROR create_face_array()]\t" \
			"Mesh face array memory allocation failed\n"));
		return (true);
	}
	return (false);
}

 char	*create_face_format(t_mesh *mesh)
{
	int		size;
	char	*format;

	if (mesh)
	{
		size = mesh->n_face[2];
		format = ft_strdup("f");
		if (mesh->n_face[3] == 0)
			while (size-- > 0)
				format = ft_strjoin_free(format, " %d", 1);
		else if (mesh->n_face[3] == 1)
			while (size-- > 0)
				format = ft_strjoin_free(format, " %d/%d", 1);
		else if (mesh->n_face[3] == 2)
			while (size-- > 0)
				format = ft_strjoin_free(format, " %d/%d/%d", 1);
		else if (mesh->n_face[3] == 3)
			while (size-- > 0)
				format = ft_strjoin_free(format, " %d//%d", 1);
		else
			return (error("[ERROR create_face_format()]\t" \
			"Mesh could not set up the face format for data reading.\n"));
		return (format);
	}
	return (NULL);
}

bool		mesh_line_process_face(t_mesh *mesh, char *str)
{
	int		index;
	char	**split;

	if (mesh && str)
	{
		if (!mesh->face && mesh->n_face[0] > 0)
		{
			if (!(mesh_get_face_type(mesh, str)))
				return (error_bool("[ERROR mesh_line_process_face()]\t" \
				"Mesh face line parsing & analysis failed!\n"));
			if (!create_face_array(mesh))
				return (error_bool("[ERROR mesh_line_process_face()]\t" \
				"Mesh face array creation failed!\n"));
			if (!(mesh->face_format = create_face_format(mesh)))
				return (error_bool("[ERROR mesh_line_process_face()]\t" \
				"Mesh face format creation failed!\n"));
		}
		index = (mesh->n_face[1]++) * mesh->n_face[2] * mesh->n_face[4];
		if (!(split = ft_strsplit(str, ' ')))
			return (error_bool("[ERROR mesh_line_process_face()]\t" \
			"Mesh could not split face line for processing its data!\n"));
		if (!(mesh_process_face(mesh, split, index)))
		{
			split_destroy(split);
			return (error_bool("[ERROR mesh_line_process_face()]\t" \
			"Could not process face data!\n"));
		}
		return (true);
	}
	return (false);
}
