/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_line_process_vn.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:53:11 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/27 18:12:21 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	mesh_line_process_vn(t_mesh *mesh, char *str)
{
	if (mesh && str)
	{
		if (!(mesh_line_process_check(str, CHARSET_VN)))
			return (!scop_log_err("[ERROR mesh_line_process_vn]\t" \
			"Wrong character found in VN line ->\t\"%s\"\n", str));
		if (!(mesh_process_normal(mesh, str)))
			return (!scop_log_err("[ERROR mesh_line_process_vn]\t" \
			"Vertex normal line processing failed ->\t%s\n", str));
		return (true);
	}
	return (error_bool("[ERROR mesh_line_process_vn]\t" \
	"NULL mesh or string pointer!\n"));
}
