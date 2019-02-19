/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_file_load.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:54:37 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/19 11:05:04 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int		mesh_file_get_size(const char *target)
{
	struct stat	file_stat;

	if (stat(target, &file_stat) != 0)
		return (-1);
	else
		return ((size_t)file_stat.st_size);
}

static char		*mesh_file_dump(const char *target, const size_t target_size)
{
	void		*data;
	int			fd;
	ssize_t		read_status;

	if (target)
	{
		if (!(data = ft_memalloc(target_size + 1)))
			return (error("[ERROR mesh_dump_data()]\t" \
							"Could not allocate memory for mesh data"));
		if ((fd = open(target, O_RDONLY)) < 0)
		{
			if (data)
				free(data);
			return (error("[ERROR mesh_dump_data()]\t" \
							"Could not open target file"));
		}
		read_status = read(fd, data, target_size);
		((char*)(data))[read_status] = 0;
		close(fd);
		return (data);
	}
	return (error("[ERROR mesh_dump_data()]\tTarget is NULL"));
}

char			*mesh_file_load(t_scop *env, const char *target)
{
	size_t		target_size;

	target_size = 0;
	if (env && target)
	{
		if ((target_size = mesh_file_get_size(target)) == -1)
			return (error("[ERROR mesh_load()]\t" \
							"Could not get target file's size"));
		return (mesh_file_dump(target, target_size));
	}
	return (NULL);
}
