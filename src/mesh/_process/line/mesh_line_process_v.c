/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_line_process_v.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:38:27 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/27 18:12:03 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	mesh_line_process_v(t_mesh *mesh, char *str)
{
	if (mesh && str)
	{
		if (!(mesh_line_process_check(str, CHARSET_V)))
			return (!scop_log_err("[ERROR mesh_line_process_v]\t" \
			"Wrong character found in V line ->\t\"%s\"\n", str));
		if (!(mesh_process_vertex(mesh, str)))
			return (!scop_log_err("[ERROR mesh_line_process_v]\t" \
			"Vertex line processing failed ->\t%s\n", str));
		return (true);
	}
	return (error_bool("[ERROR mesh_line_process_v]\t" \
	"NULL mesh or string pointer!\n"));
}
