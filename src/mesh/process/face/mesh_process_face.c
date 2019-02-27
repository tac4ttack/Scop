/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_process_face.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 12:59:37 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/27 16:14:22 by fmessina         ###   ########.fr       */
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

bool				mesh_process_face_data(t_mesh *mesh, \
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

static bool	create_face_array(t_mesh *mesh)
{
	if (mesh)
	{
		if (!(mesh->face = ft_memalloc(sizeof(int) \
										* mesh->n_face[4] \
										* mesh->n_face[2] \
										* mesh->n_face[0])))
			return (error_bool("[ERROR create_face_array]\t" \
			"Mesh face array memory allocation failed!\n"));
		return (true);
	}
	return (false);
}

static char	*create_face_format(t_mesh *mesh)
{
	int		size;
	char	*format;

	if (mesh)
	{
		size = mesh->n_face[2];
		format = ft_strdup("f");
		if (mesh->n_face[3] == 0)
			while (size-- > 0)
				format = ft_strjoin_free(format, " %d", 1);
		else if (mesh->n_face[3] == 1)
			while (size-- > 0)
				format = ft_strjoin_free(format, " %d/%d", 1);
		else if (mesh->n_face[3] == 2)
			while (size-- > 0)
				format = ft_strjoin_free(format, " %d/%d/%d", 1);
		else if (mesh->n_face[3] == 3)
			while (size-- > 0)
				format = ft_strjoin_free(format, " %d//%d", 1);
		else
			return (error("[ERROR create_face_format]\t" \
			"Mesh could not set up the face format for data reading!\n"));
		return (format);
	}
	return (NULL);
}

bool		mesh_process_face(t_mesh *mesh, char *str)
{
	int		i;
	char	**split;

	if (mesh && str)
	{
		if (!mesh->face && mesh->n_face[0] > 0)
		{
			if (!(mesh_get_face_type(mesh, str)))
				return (error_bool("[ERROR mesh_line_process_face]\t" \
				"Mesh face line parsing & analysis failed!\n"));
			if (!create_face_array(mesh))
				return (error_bool("[ERROR mesh_line_process_face]\t" \
				"Mesh face array creation failed!\n"));
			if (!(mesh->face_format = create_face_format(mesh)))
				return (error_bool("[ERROR mesh_line_process_face]\t" \
				"Mesh face format creation failed!\n"));
		}
		i = (++mesh->n_face[1] - 1) * mesh->n_face[2] * mesh->n_face[4];
		if (!(split = ft_strsplit(str, ' ')))
			return (error_bool("[ERROR mesh_line_process_face]\t" \
			"Mesh could not split face line for processing its data!\n"));
		if (!(mesh_process_face_data(mesh, split, i)))
		{
			split_destroy(split);
			return (error_bool("[ERROR mesh_line_process_face]\t" \
			"Could not process face data!\n"));
		}
		return (true);
	}
	return ((error_bool("[ERROR mesh_line_process_face]\t" \
	"NULL mesh or line pointer!\n")));
}
