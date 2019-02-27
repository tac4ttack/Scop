/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_line_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:37:40 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/27 18:26:42 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool mesh_line_preprocess(t_mesh *mesh, char **split)
{
	if (mesh && split)
	{
		while (*split)
		{
			(strncmp(*split, "v ", 2) == 0 ? mesh->n_vertex[0]++ : 0);
			(strncmp(*split, "f ", 2) == 0 ? mesh->n_face[0]++ : 0);
			(strncmp(*split, "vt ", 3) == 0 ? mesh->n_texture[0]++ : 0);
			(strncmp(*split, "vn ", 3) == 0 ? mesh->n_normal[0]++ : 0);
			(strncmp(*split, "vp ", 3) == 0 ? mesh->n_space[0]++ : 0);
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

static bool mesh_line_process_checksum(t_mesh *mesh)
{
	if (mesh)
	{
		scop_log("\nMESH DATA CHECKSUM:\nn_vertex[0] = %zu\t\t\tn_vertex[1] " \
		"= %zu\nn_face[0] = %zu\t\t\tn_face[1] = %zu\nn_normal[0] = %zu\t\t\t" \
		"n_normal[1] = %zu\nn_texture[0] = %zu\t\tn_texture[1] = %zu\n" \
		"n_space[0] = %zu\t\t\tn_space[1] = %zu\n\n", mesh->n_vertex[0], \
		mesh->n_vertex[1], mesh->n_face[0], mesh->n_face[1], \
		mesh->n_normal[0], mesh->n_normal[1], mesh->n_texture[0], \
		mesh->n_texture[1],	mesh->n_space[0], mesh->n_space[1]);
		if (mesh->n_vertex[0] != mesh->n_vertex[1]
			|| mesh->n_face[0] != mesh->n_face[1]	//carefule with the future triangulation
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
		{
			mesh_clean(mesh);
			return (error_bool("[ERROR mesh_line_process]\t" \
			"Mesh file pre processing failed!\n"));
		}
		while (*split && !(failure = mesh_line_process_dispatch(mesh, *split)))
		{
			if (failure)
			{
				mesh_clean(mesh);
				return (scop_log_err("[ERROR mesh_line_process]\t" \
				"Mesh file format is invalid! -> \"%s\"\n"));
			}
			split++;
		}
		return (mesh_line_process_checksum(mesh));
	}
	return (error_bool("[ERROR mesh_line_process]\tNULL param pointer!\n"));
}



// backup 2
/*
bool	mesh_line_process(t_mesh *mesh, char **split)
{
	if (mesh && split)
	{
		scop_log("\nMESH DATA PARSING:\n");
		if (!(mesh_line_preprocess(mesh, split)))
		{
			mesh_clean(mesh);
			return (error_bool("[ERROR mesh_line_process]\t" \
			"Mesh file pre processing failed!\n"));
		}
		while (*split)
		{
			if (strncmp(*split, "#", 1) == 0)
				scop_log("Comment found ->\t%s\n", *split);
			else if (strncmp(*split, "v ", 2) == 0)
			{
				if (mesh_line_process_vertex(mesh, *split))
					return (!scop_log_err("[ERROR mesh_line_process]\t" \
					"V line parsing failed -> |%s|\n"));
			}
			else if (strncmp(*split, "f ", 2) == 0)
			{
				if (mesh_line_process_face(mesh, *split))
					return (!scop_log_err("[ERROR mesh_line_process]\t" \
					"V line parsing failed -> |%s|\n"));
			}
			else if (strncmp(*split, "vt ", 3) == 0)
			{
				if (!(mesh_line_process_check(*split, CHARSET_VT)))
					return (!scop_log_err("[ERROR mesh_line_process]\t" \
					"Wrong character found in VT line ->\t\"%s\"\n", *split));
				if (!(mesh_line_process_texture(mesh, *split)))
					return (!scop_log_err("[ERROR mesh_line_process]\t" \
					"Texture line processing failed ->\t%s\n", *split));
			}
			else if (strncmp(*split, "vn ", 3) == 0)
			{
				if (!(mesh_line_process_check(*split, CHARSET_VN)))
					return (!scop_log_err("[ERROR mesh_line_process]\t" \
					"Wrong character found in VN line ->\t\"%s\"\n", *split));
				if (!(mesh_line_process_normal(mesh, *split)))
					return (!scop_log_err("[ERROR mesh_line_process]\t" \
					"Vertex normal line processing failed ->\t%s\n", *split));
			}
			else if ((strncmp(*split, "\n", 1) == 0)				// TEMP, parsing the rest of the obj data needs to be finished
					|| (strncmp(*split, "o ", 2) == 0)
					|| (strncmp(*split, "g ", 2) == 0)
					|| (strncmp(*split, "vp ", 1) == 0)
					|| (strncmp(*split, "l ", 1) == 0)
					|| (strncmp(*split, "mtllib ", 7) == 0)
					|| (strncmp(*split, "usemtl ", 7) == 0)
					|| (strncmp(*split, "s ", 2) == 0))
					scop_log("Skipping line ->\t%s\n", *split);
			else
			{
				mesh_clean(mesh);
				return (error_bool("[ERROR mesh_line_process]\t" \
				"Mesh file format is invalid!\n"));
			}
			split++;
		}
		if (!(mesh_line_process_checksum(mesh)))
			return (error_bool("[ERROR mesh_line_process]\t" \
				"Mesh file processing failed (number of vertices processed" \
				" != number of vertices present in file)!\n"));
		return (true);
	}
	return (error_bool("[ERROR mesh_line_process]\tNULL param pointer!\n"));
}*/

// backup de la grosse fonction
/*bool	mesh_line_process(t_mesh *mesh, char **split)
{
	if (mesh && split)
	{
		scop_log("\nMESH DATA PARSING:\n");
		if (!(mesh_line_preprocess(mesh, split)))
		{
			mesh_clean(mesh);
			return (error_bool("[ERROR mesh_line_process]\t" \
			"Mesh file pre processing failed!\n"));
		}
		while (*split)
		{
			if (strncmp(*split, "#", 1) == 0)
				scop_log("Comment found ->\t%s\n", *split);
			else if (strncmp(*split, "v ", 2) == 0)
			{
				if (!(mesh_line_process_check(*split, CHARSET_V)))
					return (!scop_log_err("[ERROR mesh_line_process]\t" \
					"Wrong character found in V line ->\t\"%s\"\n", *split));
				if (!(mesh_line_process_vertex(mesh, *split)))
					return (!scop_log_err("[ERROR mesh_line_process]\t" \
					"Vertex line processing failed ->\t%s\n", *split));
			}
			else if (strncmp(*split, "f ", 2) == 0)
			{
				if (!(mesh_line_process_check(*split, CHARSET_F)))
					return (!scop_log_err("[ERROR mesh_line_process]\t" \
					"Wrong character found in F line ->\t\"%s\"\n", *split));
				if (!(mesh_line_process_face(mesh, *split)))
					return (!scop_log_err("[ERROR mesh_line_process]\t" \
					"Face element line processing failed ->\t%s\n", *split));
			}
			else if (strncmp(*split, "vt ", 3) == 0)
			{
				if (!(mesh_line_process_check(*split, CHARSET_VT)))
					return (!scop_log_err("[ERROR mesh_line_process]\t" \
					"Wrong character found in VT line ->\t\"%s\"\n", *split));
				if (!(mesh_line_process_texture(mesh, *split)))
					return (!scop_log_err("[ERROR mesh_line_process]\t" \
					"Texture line processing failed ->\t%s\n", *split));
			}
			else if (strncmp(*split, "vn ", 3) == 0)
			{
				if (!(mesh_line_process_check(*split, CHARSET_VN)))
					return (!scop_log_err("[ERROR mesh_line_process]\t" \
					"Wrong character found in VN line ->\t\"%s\"\n", *split));
				if (!(mesh_line_process_normal(mesh, *split)))
					return (!scop_log_err("[ERROR mesh_line_process]\t" \
					"Vertex normal line processing failed ->\t%s\n", *split));
			}
			else if ((strncmp(*split, "\n", 1) == 0)				// TEMP, parsing the rest of the obj data needs to be finished
					|| (strncmp(*split, "o ", 2) == 0)
					|| (strncmp(*split, "g ", 2) == 0)
					|| (strncmp(*split, "vp ", 1) == 0)
					|| (strncmp(*split, "l ", 1) == 0)
					|| (strncmp(*split, "mtllib ", 7) == 0)
					|| (strncmp(*split, "usemtl ", 7) == 0)
					|| (strncmp(*split, "s ", 2) == 0))
					scop_log("Skipping line ->\t%s\n", *split);
			else
			{
				mesh_clean(mesh);
				return (error_bool("[ERROR mesh_line_process]\t" \
				"Mesh file format is invalid!\n"));
			}
			split++;
		}
		if (!(mesh_line_process_checksum(mesh)))
			return (error_bool("[ERROR mesh_line_process]\t" \
				"Mesh file processing failed (number of vertices processed" \
				" != number of vertices present in file)!\n"));
		return (true);
	}
	return (error_bool("[ERROR mesh_line_process]\tNULL param pointer!\n"));
}*/
