/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_file_load.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:54:37 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/27 17:09:52 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool		mesh_file_get_size(const char *target, size_t *target_size)
{
	struct stat	file_stat;

	if (stat(target, &file_stat) != 0)
		return (-1);
	else
	{
		if (S_ISDIR(file_stat.st_mode))
			return (error_bool("[ERROR mesh_file_get_size]\t" \
			"Target is a directory!\n"));
		else
		{
			*target_size = (size_t)file_stat.st_size;
			return (true);
		}
	}
}

static char		*mesh_file_dump(const int fd, const size_t target_size)
{
	void		*data;
	ssize_t		read_status;

	if (fd > 0)
	{
		if (!(data = ft_memalloc(target_size + 1)))
			return (error("[ERROR mesh_dump_data]\t" \
			"Could not allocate memory for mesh data!\n"));
		if ((read_status = read(fd, data, target_size)) != (long)target_size)
		{
			free(data);
			return (error("[ERROR mesh_file_dump]\tMesh file read failed!\n"));
		}
		((char*)(data))[read_status] = 0;
		close(fd);
		scop_log("Mesh file successfully loaded!\n");
		return (data);
	}
	return (error("[ERROR mesh_dump_data]\tFile Descriptor is invalid!\n"));
}

char			*mesh_file_load(t_scop *env, char *target)
{
	size_t		target_size;
	int			fd;

	target_size = 0;
	fd = 0;
	if (env && target)
	{
		scop_log("\nLoading mesh...\n");
		if ((fd = open(target, O_RDONLY)) < 0)
			return (error("[ERROR mesh_file_load]\t" \
			"Could not open target file!\n"));
		if (!(mesh_file_get_size(target, &target_size)))
			return (error("[ERROR mesh_file_load]\t" \
			"Could not get target file's size!\n"));
		return (mesh_file_dump(fd, target_size));
	}
	return (NULL);
}
