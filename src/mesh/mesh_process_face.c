/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_process_face.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 12:59:37 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/27 12:41:51 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool			process_face_v(t_mesh *mesh, \
									char *format, \
									char **split, \
									size_t index)
{
	size_t			i;
	int				ret;
	char			**bak;

	if (mesh && split && format)
	{
		bak = split;
		ret = 0;
		i = 0;
		split++;
		while (i < mesh->n_face[5] && *split)
		{
			ret += sscanf(*split, " %d", &mesh->face[index + i]);
			/// RAJOUT GESTION INDICES NEGATIFS
			i++;
			format += 3;
			split++;
		}
		split_destroy(bak);
		if (ret != (int)mesh->n_face[5])
			return (error_bool("[ERROR process_face_v]\t" \
			"Error processing Vn face!\n"));
		return (true);
	}
	return (false);
}

static bool			process_face_v_vt(t_mesh *mesh, \
										char *format, \
										char **split, \
										size_t index)
{
	size_t			i;
	int				ret;
	char			**bak;

	if (mesh && split && format)
	{
		bak = split;
		ret = 0;
		i = 0;
		split++;
		while (i < mesh->n_face[5] && *split)
		{
			ret += sscanf(*split, " %d/%d", &mesh->face[index + i], \
						&mesh->face[index + i + 1]);
			/// RAJOUT GESTION INDICES NEGATIFS
			i += 2;
			format += 6;
			split++;
		}
		split_destroy(bak);
		if (ret != (int)mesh->n_face[5])
			return (error_bool("[ERROR process_face_v_vt]\t" \
			"Error processing Vn/VTn face!\n"));
		return (true);
	}
	return (false);
}

static bool			process_face_v_vt_vn(t_mesh *mesh, \
										char *format, \
										char **split, \
										size_t index)
{
	size_t			i;
	int				ret;
	char			**bak;

	if (mesh && split && format)
	{
		bak = split;
		ret = 0;
		i = 0;
		split++;
		while (i < mesh->n_face[5] && *split)
		{
			ret += sscanf(*split, " %d/%d/%d", &mesh->face[index + i], \
						&mesh->face[index + i + 1], &mesh->face[index + i + 2]);
			/// RAJOUT GESTION INDICES NEGATIFS
			i += 3;
			format += 9;
			split++;
		}
		split_destroy(bak);
		if (ret != (int)mesh->n_face[5])
			return (error_bool("[ERROR process_face_v_vt_vn]\t" \
			"Error processing Vn/VTn/VNn face!\n"));
		return (true);
	}
	return (false);
}

static bool			process_face_v_vn(t_mesh *mesh, \
										char *format, \
										char **split, \
										size_t index)
{
	size_t			i;
	int				ret;
	char			**bak;

	if (mesh && split && format)
	{
		bak = split;
		ret = 0;
		i = 0;
		split++;
		while (i < mesh->n_face[5] && *split)
		{
			ret += sscanf(*split, " %d//%d", &mesh->face[index + i], \
						&mesh->face[index + i + 1]);
			/// RAJOUT GESTION INDICES NEGATIFS
			i += 2;
			format += 7;
			split++;
		}
		split_destroy(bak);
		if (ret != (int)mesh->n_face[5])
			return (error_bool("[ERROR mesh_process_face_v_vn]\t" \
			"Error processing Vn//VNn face!\n"));
		return (true);
	}
	return (false);
}

bool				mesh_process_face(t_mesh *mesh, \
										char **split, \
										size_t index)
{
	if (mesh && split)
	{
		if (mesh->n_face[3] == 0)
			return (process_face_v(mesh, (mesh->face_format + 2), \
			split, index));
		else if (mesh->n_face[3] == 1)
			return (process_face_v_vt(mesh, (mesh->face_format + 2), \
			split, index));
		else if (mesh->n_face[3] == 2)
			return (process_face_v_vt_vn(mesh, (mesh->face_format + 2), \
			split, index));
		else if (mesh->n_face[3] == 3)
			return (process_face_v_vn(mesh, (mesh->face_format + 2), \
			split, index));
		else
			return (error_bool("[ERROR mesh_process_face]\t" \
			"Error processing face, format unknown!\n"));
	}
	return (false);
}
