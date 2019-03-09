/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_process_face_data.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:53:33 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/09 15:14:18 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool	mesh_process_face_data_v(t_mesh *mesh, char *str, int index)
{
	int		ret;

	if (mesh && str)
	{
		ret = sscanf(str, "%d", &mesh->face[index]);
		if (ret != 1)
			return (error_bool("[ERROR mesh_process_face_data_v]\t" \
			"Could not retrieve Vn face element data!\n"));
		else if (mesh->face[index] == 0)
			return (error_bool("[ERROR mesh_process_face_data_v]\t" \
			"Error in face element format, indices can\'t be 0!\n"));
		mesh->face[index + 1] = -1;
		mesh->face[index + 2] = -1;
		return (true);
	}
	return (error_bool("[ERROR mesh_process_face_data_v]\t" \
	"NULL mesh or string pointer!\n"));
}

static bool	mesh_process_face_data_v_vt(t_mesh *mesh, char *str, int index)
{
	int		ret;

	if (mesh && str)
	{
		ret = sscanf(str, "%d/%d", &mesh->face[index], &mesh->face[index + 1]);
		if (ret != 2)
			return (error_bool("[ERROR mesh_process_face_data_v_vt]\t" \
			"Could not retrieve Vn/VTn face element data!\n"));
		else if (mesh->face[index] == 0 || mesh->face[index + 1] == 0)
			return (error_bool("[ERROR mesh_process_face_data_v_vt]\t" \
			"Error in face element format, indices can\'t be 0!\n"));
		mesh->face[index + 2] = -1;
		return (true);
	}
	return (error_bool("[ERROR mesh_process_face_data_v_vt]\t" \
	"NULL mesh or string pointer!\n"));
}

static bool	mesh_process_face_data_v_vt_vn(t_mesh *mesh, char *str, int index)
{
	int		ret;

	if (mesh && str)
	{
		ret = sscanf(str, "%d/%d/%d", \
					&mesh->face[index],
					&mesh->face[index + 1],
					&mesh->face[index + 2]);
		if (ret != 3)
			return (error_bool("[ERROR mesh_process_face_data_v_vt_vn]\t" \
			"Could not retrieve Vn/VTn/VNn face element data!\n"));
		else if (mesh->face[index] == 0 \
					|| mesh->face[index + 1] == 0
					|| mesh->face[index + 2] == 0)
			return (error_bool("[ERROR mesh_process_face_data_v_vt_vn]\t" \
			"Error in face element format, indices can\'t be 0!\n"));
		return (true);
	}
	return (error_bool("[ERROR mesh_process_face_data_v_vt_vn]\t" \
	"NULL mesh or string pointer!\n"));
}

static bool	mesh_process_face_data_v_vn(t_mesh *mesh, char *str, int index)
{
	int		ret;

	if (mesh && str)
	{
		ret = sscanf(str, "%d//%d", &mesh->face[index], &mesh->face[index + 2]);
		if (ret != 2)
			return (error_bool("[ERROR mesh_process_face_data_v_vn]\t" \
			"Could not retrieve Vn//VNn face element data!\n"));
		else if (mesh->face[index] == 0 || mesh->face[index + 2] == 0)
			return (error_bool("[ERROR mesh_process_face_data_v_vn]\t" \
			"Error in face element format, indices can\'t be 0!\n"));
		mesh->face[index + 1] = -1;
		return (true);
	}
	return (error_bool("[ERROR mesh_process_face_data_v_vn]\t" \
	"NULL mesh or string pointer!\n"));
}

bool		mesh_process_face_data_dispatch(t_mesh *mesh, \
											char *str, \
											int mod, \
											int index)
{
	if (mesh && str && mod >= 0 && mod <= 3)
	{
		if (mod == 0)
			return (mesh_process_face_data_v(mesh, str, index));
		else if (mod == 1)
			return (mesh_process_face_data_v_vt(mesh, str, index));
		else if (mod == 2)
			return (mesh_process_face_data_v_vt_vn(mesh, str, index));
		else if (mod == 3)
			return (mesh_process_face_data_v_vn(mesh, str, index));
		else
			return (false);
	}
	return (error_bool("[ERROR mesh_process_face_data_dispatch]\t" \
	"NULL mesh or string pointer, or invalid face mod!\n"));
}
