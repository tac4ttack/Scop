/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_print_data_face.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 15:09:07 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/23 18:34:12 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	print_data_face_v_vt(t_mesh *mesh, size_t index)
{
	size_t	i;

	if (mesh)
	{
		i = 0;
		while (i < mesh->n_face[5])
		{
			scop_log("\t%d/%d", \
					mesh->face[index + i], \
					mesh->face[index + i + 1]);
			i += 2;
		}
	}
}

static void	print_data_face_v_vt_vn(t_mesh *mesh, size_t index)
{
	size_t	i;

	if (mesh)
	{
		i = 0;
		while (i < mesh->n_face[5])
		{
			scop_log("\t%d/%d/%d", \
					mesh->face[index + i], \
					mesh->face[index + i + 1], \
					mesh->face[index + i + 2]);
			i += 3;
		}
	}
}

static void	print_data_face_v_vn(t_mesh *mesh, size_t index)
{
	size_t	i;

	if (mesh)
	{
		i = 0;
		while (i < mesh->n_face[5])
		{
			scop_log("\t%d//%d", \
					mesh->face[index + i], \
					mesh->face[index + i + 1]);
			i += 2;
		}
	}
}

void		mesh_print_data_face(t_mesh *mesh)
{
	size_t	i[2];

	i[0] = 0;
	i[1] = 0;
	scop_log("Face data =\n-----------", NULL);
	while (i[0] < mesh->n_face[1])
	{
		scop_log("\nf[%d]\t=", i[0]);
		if (mesh->n_face[3] == 0)
			while (i[1] < mesh->n_face[5])
				scop_log("\t%d", mesh->face[(i[0] * mesh->n_face[5]) + i[1]++]);
		else if (mesh->n_face[3] == 1)
			print_data_face_v_vt(mesh, (i[0] * mesh->n_face[5]));
		else if (mesh->n_face[3] == 2)
			print_data_face_v_vt_vn(mesh, (i[0] * mesh->n_face[5]));
		else if (mesh->n_face[3] == 3)
			print_data_face_v_vn(mesh, (i[0] * mesh->n_face[5]));
		i[0]++;
		i[1] = 0;
	}
}

void		mesh_print_data_face_type(t_mesh *mesh)
{
	if (mesh)
	{
		if (mesh->n_face[3] == 0)
			scop_log("\nFaces type = %d Vn\n", mesh->n_face[2]);
		else if (mesh->n_face[3] == 1)
			scop_log("\nFaces type = %d Vn/VTn\n", mesh->n_face[2]);
		else if (mesh->n_face[3] == 2)
			scop_log("\nFaces type = %d Vn/VTn/VNn\n", mesh->n_face[2]);
		else if (mesh->n_face[3] == 3)
			scop_log("\nFaces type = %d Vn//VNn\n", mesh->n_face[2]);
		else
			scop_log("\nCan't determine what type of data faces type =!");
	}
}
