/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_line_process_vp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:53:11 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/27 18:12:16 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	mesh_line_process_vp(t_mesh *mesh, char *str)
{
	if (mesh && str)
	{
		if (!(mesh_line_process_check(str, CHARSET_VP)))
			return (!scop_log_err("[ERROR mesh_line_process_vp]\t" \
			"Wrong character found in VP line ->\t\"%s\"\n", str));
		if (!(mesh_process_space(mesh, str)))
			return (!scop_log_err("[ERROR mesh_line_process_vp]\t" \
			"Vertex space paremeter line processing failed ->\t%s\n", str));
		return (true);
	}
	return (error_bool("[ERROR mesh_line_process_vp]\t" \
	"NULL mesh or string pointer!\n"));
}
