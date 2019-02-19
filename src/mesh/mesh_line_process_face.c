/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_line_process_face.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 12:59:37 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/19 19:22:00 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool create_face_array(t_mesh *mesh)
{
	if (mesh)
	{
		if (!(mesh->face = ft_memalloc(sizeof(int) * mesh->n_face_vertex * 3)))
			return (error_bool("[ERROR create_face_array()]\t" \
			"Mesh face array memory allocation failed"));
		mesh->n_face = 1;
		return (true);
	}
	return (false);
}

static bool	extend_face_array(t_mesh *src)
{
	int		*new;

	if (src)
	{
		if (!(new = ft_memalloc(sizeof(int) \
					* (src->n_face + 1) * src->n_face_vertex * 3)))
			return (error_bool("[ERROR extend_face_array()]\t" \
			"New mesh face array memory allocation failed"));
		if (!(new = ft_memcpy(new, src->face, (sizeof(int) \
					* (src->n_face) * src->n_face_vertex))))
			return (error_bool("[ERROR extend_face_array()]\t" \
			"Old mesh face array data copy to new array failed"));
		src->n_face++;
		free(src->face);
		src->face = new;
		return (true);
	}
	return (false);
}

static bool		get_face_vertex_count(t_mesh *mesh, char *str)
{
	char		**split;

	if (str)
	{
		if (!(split = ft_strsplit(str, ' ')))
			return (error_bool("[ERROR get_face_vertex_count()]\t" \
				"Can't split face line to count its vertices"));
		while (*(split + mesh->n_face_vertex))
			mesh->n_face_vertex++;
		mesh->n_face_vertex--;
		split_destroy(split);
		fprintf(stdout, "DEBUG ->\tn_face_vertex = %d\n", mesh->n_face_vertex);
		return (true);
	}
	return (false);
}

static bool		mesh_extract_face_data(t_mesh *mesh, char **split)
{
	int		index = (mesh->n_face - 1) * mesh->n_face_vertex;
	// int		check = 0;
	int		ret = 0;

	if (mesh && ++split)
	{
		fprintf(stdout, "DEBUG ->\tindex = %d\n", index);
		while (*split)
		{
			ret = sscanf(*split, "%d/%d/%d", \
					&mesh->face[index], &mesh->face[index + 1], &mesh->face[index + 2]);
			fprintf(stdout, "DEBUG ->\tret = %d\t'%s'\n", ret, *split);
			split++;
			// check++;
			// index += 3;
		}
		// if (check / 3 != mesh->n_face_vertex)
			// return (error_bool("wrong number of vertices for a face"));
		return (true);
	}
	if (split)
		split_destroy(split);
	return (false);
}

bool			mesh_line_process_face(t_mesh *mesh, char *str)
{
	if (mesh && str)
	{
		if (mesh->n_face == 0)
		{
			if (!(get_face_vertex_count(mesh, str)))
				return (error_bool("[ERROR mesh_line_process_face()]\t" \
				"Mesh face line parsing & analysis failed"));
		}
		if (!mesh->face)
		{
			if (!create_face_array(mesh))
				return (error_bool("[ERROR mesh_line_process_face()]\t" \
				"Mesh face array creation failed"));
		}
		else
		{
			if (!extend_face_array(mesh))
				return (error_bool("[ERROR mesh_line_process_face()]\t" \
				"Mesh face array extension failed"));
		}
		if (!(mesh_extract_face_data(mesh, ft_strsplit(str, ' '))))
			return (error_bool("[ERROR mesh_line_process_face()]\t" \
				"Mesh face line analysis failed"));
		return (true);
	}
	return (false);
}
