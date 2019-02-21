/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_line_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:37:40 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/21 18:57:05 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	mesh_line_process(t_mesh *mesh, char **split)
{
	if (mesh && split)
	{
		scop_log("\nMESH DATA PARSING:\n");
		while (*split)
		{
			if (strncmp(*split, "#", 1) == 0)
				scop_log("Comment found ->\t%s\n", *split);
			else if (strncmp(*split, "v ", 2) == 0)
			{
				if (!(mesh_line_check(*split, CHARSET_V)))
				{
					mesh_clean(mesh);
					return (!scop_log_err("\nWrong character found in V line ->\t\"%s\"\n", *split));
				}
				if (!(mesh_line_process_vertex(mesh, *split)))
					return (error_bool("[ERROR mesh_line_process()]\t" \
					"Vertex line processing failed\n"));
			}
			else if (strncmp(*split, "f ", 2) == 0)
			{
				if (!(mesh_line_check(*split, CHARSET_F)))
				{
					mesh_clean(mesh);
					return (!scop_log_err("\nWrong character found in F line ->\t\"%s\"\n", *split));
				}
				if (!(mesh_line_process_face(mesh, *split)))
					return (error_bool("[ERROR mesh_line_process()]\t" \
					"Face element line processing failed\n"));
			}
			else if ((strncmp(*split, "\n", 1) == 0)				// TEMP, parsing the rest of the obj data needs to be finished
					|| (strncmp(*split, "o ", 2) == 0)
					|| (strncmp(*split, "g ", 2) == 0)
					|| (strncmp(*split, "vt ", 1) == 0)
					|| (strncmp(*split, "vn ", 1) == 0)
					|| (strncmp(*split, "vp ", 1) == 0)
					|| (strncmp(*split, "l ", 1) == 0)
					|| (strncmp(*split, "mtllib ", 7) == 0)
					|| (strncmp(*split, "usemtl ", 7) == 0)
					|| (strncmp(*split, "s ", 2) == 0))
					scop_log("Useless line found skipping ->\t%s\n", *split);
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
		return (true);
	}
	return (false);
}
