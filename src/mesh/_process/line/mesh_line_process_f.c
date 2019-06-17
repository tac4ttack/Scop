/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_line_process_f.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 12:59:37 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/28 15:56:57 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"


bool	mesh_line_process_f(t_mesh *mesh, char *str)
{
	if (mesh && str)
	{
		if (!(mesh_line_process_check(str, CHARSET_F)))
			return (!scop_log_err("[ERROR mesh_line_process_f]\t" \
			"Wrong character found in F line ->\t\"%s\"\n", str));
		if (!(mesh_process_face(mesh, str)))
			return (!scop_log_err("[ERROR mesh_line_process_f]\t" \
			"Face element line processing failed ->\t%s\n", str));
		return (true);
	}
	return (error_bool("[ERROR mesh_line_process_f]\t"\
	"NULL mesh or string pointer!\n"));
}
