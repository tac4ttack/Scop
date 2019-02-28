/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_line_process_vt.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:12:03 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/28 14:45:04 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	mesh_line_process_vt(t_mesh *mesh, char *str)
{
	if (mesh && str)
	{
		if (!(mesh_line_process_check(str, CHARSET_VT)))
			return (!scop_log_err("[ERROR mesh_line_process_vt]\t" \
			"Wrong character found in VT line ->\t\"%s\"\n", str));
		if (!(mesh_process_texture(mesh, str)))
			return (!scop_log_err("[ERROR mesh_line_process_vt]\t" \
			"Texture line processing failed ->\t%s\n", str));
		return (true);
	}
	return (error_bool("[ERROR mesh_line_process_vt]\t" \
	"NULL mesh or string pointer!\n"));
}
