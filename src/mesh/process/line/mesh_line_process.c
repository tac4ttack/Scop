/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_line_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:37:40 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/28 11:51:12 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool	validate_face_element(t_mesh *mesh, char *str)
{
	int		i;
	char	**face_split[2];

	if (mesh && str)
	{
		i = -1;
		if (!(face_split[0] = ft_strsplit(str, ' ')))
			return (error_bool("[ERROR validate_face_element]\t" \
			"Split for validating face element failed!\n"));
		face_split[1] = face_split[0];
		while (*face_split[0] && i++ < 5)
			face_split[0]++;
		split_destroy(face_split[1]);
		if (i > 4)
			return (!(scop_log_err("[ERROR validate_face_element]\t" \
			"Face element is not a triangle or a quad! ->\t %s\n", str)));
		else if (i == 4)
			mesh->n_face[0] += 2;
		else
			mesh->n_face[0] += 1;
		return (true);
	}
	return (error_bool("[ERROR validate_face_element]\t" \
	"NULL mesh or string pointer!\n"));
}

static bool	mesh_line_preprocess(t_mesh *mesh, char **split)
{
	if (mesh && split)
	{
		while (*split)
		{
			(strncmp(*split, "v ", 2) == 0 ? mesh->n_vertex[0]++ : 0);
			(strncmp(*split, "vt ", 3) == 0 ? mesh->n_texture[0]++ : 0);
			(strncmp(*split, "vn ", 3) == 0 ? mesh->n_normal[0]++ : 0);
			(strncmp(*split, "vp ", 3) == 0 ? mesh->n_space[0]++ : 0);
			if (strncmp(*split, "f ", 2) == 0)
				if (!(validate_face_element(mesh, *split)))
					return (error_bool("[ERROR mesh_line_preprocess]\t" \
					"Face elements must be triangles or quads only!\n"));
			split++;
		}
		if (mesh->n_vertex[0] < 3)
			return (error_bool("[ERROR mesh_line_preprocess]\t" \
			"The mesh needs at lest 3 vertices!\n"));
		scop_log("Preprocessing results:\n%zu Vertices\n%zu Polygons\n%zu Ve" \
		"rtex texture coordinates\n%zu Vertex normals\n%zu Space vertices\n", \
		mesh->n_vertex[0], mesh->n_face[0], mesh->n_texture[0], \
		mesh->n_normal[0], mesh->n_space[0]);
		return (true);
	}
	return (error_bool("[ERROR mesh_line_preprocess]\t" \
	"NULL mesh or split pointer!\n"));
}

static bool	mesh_line_process_checksum(t_mesh *mesh)
{
	if (mesh)
	{
		scop_log("\nMESH DATA CHECKSUM:\nn_vertex[0] = %zu\t\t\tn_vertex[1] " \
		"= %zu\nn_face[0] = %zu\t\t\tn_face[1] = %zu\nn_normal[0] = %zu\t\t\t" \
		"n_normal[1] = %zu\nn_texture[0] = %zu\t\tn_texture[1] = %zu\n" \
		"n_space[0] = %zu\t\t\tn_space[1] = %zu\n\n", mesh->n_vertex[0], \
		mesh->n_vertex[1], mesh->n_face[0], mesh->n_face[1], \
		mesh->n_normal[0], mesh->n_normal[1], mesh->n_texture[0], \
		mesh->n_texture[1], mesh->n_space[0], mesh->n_space[1]);
		if (mesh->n_vertex[0] != mesh->n_vertex[1]
			|| mesh->n_face[0] != mesh->n_face[1]
			|| mesh->n_normal[0] != mesh->n_normal[1]
			|| mesh->n_texture[0] != mesh->n_texture[1]
			|| mesh->n_space[0] != mesh->n_space[1])
			return (error_bool("[ERROR mesh_line_process_checksum]\t" \
			"Mesh file processing failed, amount of data preprocessed" \
			" is different from amount of data processed!\n"));
		return (true);
	}
	return (error_bool("[ERROR mesh_line_process_checksum]\t" \
	"NULL mesh pointer!\n"));
}

static bool	mesh_line_process_dispatch(t_mesh *mesh, char *str)
{
	bool	failure;

	if (mesh && str)
	{
		failure = false;
		if (strncmp(str, "v ", 2) == 0)
			failure = mesh_line_process_v(mesh, str);
		else if (strncmp(str, "f ", 2) == 0)
			failure = mesh_line_process_f(mesh, str);
		else if (strncmp(str, "vt ", 3) == 0)
			failure = mesh_line_process_vt(mesh, str);
		else if (strncmp(str, "vn ", 3) == 0)
			failure = mesh_line_process_vn(mesh, str);
		else if (strncmp(str, "vp ", 3) == 0)
			failure = mesh_line_process_vp(mesh, str);
		return (failure);
	}
	return (!(error_bool("[ERROR mesh_line_process_dispatch]\t" \
	"NULL mesh or string pointer!\n")));
}

bool		mesh_line_process(t_mesh *mesh, char **split)
{
	bool	failure;

	if (mesh && split)
	{
		failure = false;
		scop_log("\nMESH DATA PARSING:\n");
		if (!(mesh_line_preprocess(mesh, split)))
			return (error_bool("[ERROR mesh_line_process]\t" \
			"Mesh file pre processing failed!\n"));
		while (*split && !(failure = mesh_line_process_dispatch(mesh, *split)))
		{
			if (failure)
				return (scop_log_err("[ERROR mesh_line_process]\t" \
				"Mesh file format is invalid! -> \"%s\"\n"));
			split++;
		}
		return (mesh_line_process_checksum(mesh));
	}
	return (error_bool("[ERROR mesh_line_process]\tNULL param pointer!\n"));
}
