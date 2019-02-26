/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_line_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:37:40 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/26 17:05:58 by fmessina         ###   ########.fr       */
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
			(strncmp(*split, "l ", 2) == 0 ? mesh->n_line[0]++ : 0);
			split++;
		}
		if (mesh->n_vertex[0] < 3)
			return (error_bool("[ERROR mesh_line_preprocess()]\t" \
			"The mesh needs at lest 3 vertices!\n"));
		scop_log("Preprocessing results:\n%zu Vertices\n%zu Polygons\n%zu " \
		"Vertex texture coordinates\n%zu Vertex normals\n%zu Space vertices\n" \
		"%zu Polylines\n", \
		mesh->n_vertex[0], mesh->n_face[0], mesh->n_texture[0], \
		mesh->n_normal[0], mesh->n_space[0], mesh->n_line[0]);
		//
		//
		return (true);
	}
	return (false);
}

static bool mesh_line_process_checksum(t_mesh *mesh)
{
	if (mesh)
	{
		fprintf(stdout, "\nDEBUG LINE CHECKSUM:\n" \
		"n_vertex[0] = %zu\t\t\tn_vertex[1] = %zu\n" \
		"n_face[0] = %zu\t\t\tn_face[1] = %zu\n" \
		"n_normal[0] = %zu\t\t\tn_normal[1] = %zu\n" \
		"n_texture[0] = %zu\t\t\tn_texture[1] = %zu\n" \
		"n_space[0] = %zu\t\t\t\tn_space[1] = %zu\n" \
		"n_line[0] = %zu\t\t\t\tn_line[1] = %zu\n\n", \
		mesh->n_vertex[0], mesh->n_vertex[1],
			mesh->n_face[0], mesh->n_face[1],
			mesh->n_normal[0], mesh->n_normal[1],
			mesh->n_texture[0], mesh->n_texture[1],
			mesh->n_space[0], mesh->n_space[1],
			mesh->n_line[0], mesh->n_line[1]);

		if (mesh->n_vertex[0] != mesh->n_vertex[1]
			|| mesh->n_face[0] != mesh->n_face[1]
			|| mesh->n_normal[0] != mesh->n_normal[1]
			|| mesh->n_texture[0] != mesh->n_texture[1]
			|| mesh->n_space[0] != mesh->n_space[1]
			|| mesh->n_line[0] != mesh->n_line[1]
			)
			return (false);
		return (true);
	}
	return (false);
}

bool	mesh_line_process(t_mesh *mesh, char **split)
{
	if (mesh && split)
	{
		scop_log("\nMESH DATA PARSING:\n");
		if (!(mesh_line_preprocess(mesh, split)))
		{
			mesh_clean(mesh);
			return (error_bool("[ERROR mesh_line_process()]\t" \
			"Mesh file pre processing failed!\n"));
		}
		while (*split)
		{
			if (strncmp(*split, "#", 1) == 0)
				; // scop_log("Comment found ->\t%s\n", *split);
			else if (strncmp(*split, "v ", 2) == 0)
			{
				if (!(mesh_line_check(*split, CHARSET_V)))
					return (!scop_log_err("[ERROR mesh_line_process()]\t" \
					"Wrong character found in V line ->\t\"%s\"\n", *split));
				if (!(mesh_line_process_vertex(mesh, *split)))
					return (!scop_log_err("[ERROR mesh_line_process()]\t" \
					"Vertex line processing failed ->\t%s\n", *split));
			}
			else if (strncmp(*split, "f ", 2) == 0)
			{
				if (!(mesh_line_check(*split, CHARSET_F)))
					return (!scop_log_err("[ERROR mesh_line_process()]\t" \
					"Wrong character found in F line ->\t\"%s\"\n", *split));
				if (!(mesh_line_process_face(mesh, *split)))
					return (!scop_log_err("[ERROR mesh_line_process()]\t" \
					"Face element line processing failed ->\t%s\n", *split));
			}
			else if (strncmp(*split, "vt ", 3) == 0)
			{
				if (!(mesh_line_check(*split, CHARSET_VT)))
					return (!scop_log_err("[ERROR mesh_line_process()]\t" \
					"Wrong character found in VT line ->\t\"%s\"\n", *split));
				if (!(mesh_line_process_texture(mesh, *split)))
					return (!scop_log_err("[ERROR mesh_line_process()]\t" \
					"Texture line processing failed ->\t%s\n", *split));
			}
			else if (strncmp(*split, "vn ", 3) == 0)
			{
				if (!(mesh_line_check(*split, CHARSET_VN)))
					return (!scop_log_err("[ERROR mesh_line_process()]\t" \
					"Wrong character found in VN line ->\t\"%s\"\n", *split));
				if (!(mesh_line_process_normal(mesh, *split)))
					return (!scop_log_err("[ERROR mesh_line_process()]\t" \
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
				return (error_bool("[ERROR mesh_line_process()]\t" \
				"Mesh file format is invalid!\n"));
			}
			split++;
			// (strncmp(*split, "vt ", 3) == 0 ? fprintf(stdout, "got a VT ->\t%s\n", *split) : 0);
			// (strncmp(*split, "vn ", 3) == 0 ? fprintf(stdout, "got a VN ->\t%s\n", *split) : 0);
			// (strncmp(*split, "vp ", 3) == 0 ? fprintf(stdout, "got a VP ->\t%s\n", *split) : 0);
			// (strncmp(*split, "l ", 2) == 0 ? fprintf(stdout, "got a L ->\t%s\n", *split) : 0);
			// (strncmp(*split, "o ", 2) == 0 ? fprintf(stdout, "got a O ->\t%s\n", *split) : 0);
			// (strncmp(*split, "g ", 2) == 0 ? fprintf(stdout, "got a G ->\t%s\n", *split) : 0);
			// (strncmp(*split, "usemtl ", 7) == 0 ? fprintf(stdout, "got a USEMTL ->\t%s\n", *split) : 0);
			// (strncmp(*split, "mtllib ", 7) == 0 ? fprintf(stdout, "got a MTLLIB ->\t%s\n", *split) : 0);
			// (strncmp(*split, "s ", 2) == 0 ? fprintf(stdout, "got a S ->\t%s\n", *split) : 0);

		}
		if (!(mesh_line_process_checksum(mesh)))
			return (error_bool("[ERROR mesh_line_process()]\t" \
				"Mesh file processing failed (number of vertices processed" \
				" != number of vertices present in file)!\n"));
		return (true);
	}
	return (false);
}
