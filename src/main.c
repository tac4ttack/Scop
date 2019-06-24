/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 14:05:26 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/24 15:53:41 by fmessina         ###   ########.fr       */
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
		if (!(env->mesh = obj_load_file(av[1])))
			exit_fail("Could not load targeted mesh file with simpleOBJ parser:(", env);
		
		//DEBBBUUUUG
		// obj_print_data(env->mesh);

		if (!(mesh_prepack(env)))
			exit_fail("Failed to pack data for OpenGL :(", env);

		//DEBUGGGGGGG
		// mesh_print_data_packed_ebo(env);
		// mesh_print_data_packed_vao(env);
		
		if (!(shader_build(env)))
			exit_fail("Could create the shader program :(", env);
		if (!(buffer_create(env)))
			exit_fail("Could create vertex buffers :(", env);
		if (!(glfw_main_loop(env)))
			exit_fail("Exception caught in GLFW main loop! :(", env);
		exit_ok(env);
	}
	else
		exit_fail("Usage: scop [mesh.obj]", NULL);
	return (0);
}
