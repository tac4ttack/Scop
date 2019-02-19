/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 14:05:26 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/19 20:00:35 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int main(int ac, char **av)
{
	t_scop *env;

	if (ac == 2 && av[1])
	{
		if (!(env = init(av[1])))
			exit_fail("Could not initialize Scop :(", env);
		if (!(env->mesh_data = mesh_file_load(env, av[1])))
			exit_fail("Could not load targeted mesh file :(", env);
		if (!(env->mesh = mesh_file_process(env)))
			exit_fail("Could not process targeted mesh file :(", env);
		if (!(shader_build(env)))
			exit_fail("Could create the shader program :(", env);
		if (!(glfw_launch(env)))
			exit_fail("Exception caught! :(", env);
		exit_ok(env);
	}
	else
		exit_fail("Usage: scop [mesh.obj]", NULL);
	return (0);
}
