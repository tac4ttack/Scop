/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_line_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:37:40 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/19 19:24:01 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	mesh_line_process(t_mesh *mesh, char **split)
{
	if (mesh && split)
	{
		scop_log("MESH DATA PARSING:\n", NULL);
		while (*split)
		{
			(ft_strncmp(*split, "#", 1) == 0 ? scop_log("comment found ->\t%s", *split) : 0);
			(ft_strncmp(*split, "v ", 2) == 0 ? mesh_line_process_vertex(mesh, *split) : 0);
			// (ft_strncmp(*split, "f ", 2) == 0 ? mesh_line_process_face(mesh, *split) : 0);

			// (ft_strncmp(*split, "vt ", 3) == 0 ? fprintf(stdout, "got a VT ->\t%s\n", *split) : 0);
			// (ft_strncmp(*split, "vn ", 3) == 0 ? fprintf(stdout, "got a VN ->\t%s\n", *split) : 0);
			// (ft_strncmp(*split, "vp ", 3) == 0 ? fprintf(stdout, "got a VP ->\t%s\n", *split) : 0);
			// (ft_strncmp(*split, "l ", 2) == 0 ? fprintf(stdout, "got a L ->\t%s\n", *split) : 0);
			// (ft_strncmp(*split, "o ", 2) == 0 ? fprintf(stdout, "got a O ->\t%s\n", *split) : 0);
			// (ft_strncmp(*split, "g ", 2) == 0 ? fprintf(stdout, "got a G ->\t%s\n", *split) : 0);
			// (ft_strncmp(*split, "usemtl ", 7) == 0 ? fprintf(stdout, "got a USEMTL ->\t%s\n", *split) : 0);
			// (ft_strncmp(*split, "mtllib ", 7) == 0 ? fprintf(stdout, "got a MTLLIB ->\t%s\n", *split) : 0);
			// (ft_strncmp(*split, "s ", 2) == 0 ? fprintf(stdout, "got a S ->\t%s\n", *split) : 0);
			split++;
		}
		return (true);
	}
	return (false);
}
