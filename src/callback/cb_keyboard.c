/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_keyboard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:35:13 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/17 11:23:07 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		cb_keyboard(GLFWwindow* window, \
						int key, \
						int scancode, \
						int action, \
						int mods)
{
	t_scop	*env;
	int		param[4];

	param[0] = key;
	param[1] = scancode;
	param[2] = action;
	param[3] = mods;

	env = glfwGetWindowUserPointer(window);

	// OTHERS INTERACTIONS
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, 1);

	else if (glfwGetKey(window, GLFW_KEY_1) || glfwGetKey(window, GLFW_KEY_2) \
		|| glfwGetKey(window, GLFW_KEY_3))
		glfw_poly_mode(param[0]);

	// MESH INTERACTION
	else if (glfwGetKey(window, GLFW_KEY_W) || glfwGetKey(window, GLFW_KEY_S) \
		|| glfwGetKey(window, GLFW_KEY_A) || glfwGetKey(window, GLFW_KEY_Q) \
		|| glfwGetKey(window, GLFW_KEY_D) || glfwGetKey(window, GLFW_KEY_E))
		mesh_translate(env, param[0]);

	// else if (glfwGetKey(window, GLFW_KEY_F13) || glfwGetKey(window, GLFW_KEY_F15) \
	// 	|| glfwGetKey(window, GLFW_KEY_HOME) || glfwGetKey(window, GLFW_KEY_DELETE) \
	// 	|| glfwGetKey(window, GLFW_KEY_END) || glfwGetKey(window, GLFW_KEY_PAGE_DOWN))
	else if (glfwGetKey(window, GLFW_KEY_I) || glfwGetKey(window, GLFW_KEY_K) \
		|| glfwGetKey(window, GLFW_KEY_O) || glfwGetKey(window, GLFW_KEY_J) \
		|| glfwGetKey(window, GLFW_KEY_U) || glfwGetKey(window, GLFW_KEY_L))
		mesh_rotate_self(env, param[0]);

	// else if (glfwGetKey(window, GLFW_KEY_KP_ADD) \
	// 	|| glfwGetKey(window, GLFW_KEY_KP_SUBTRACT))
	else if (glfwGetKey(window, GLFW_KEY_N) \
		|| glfwGetKey(window, GLFW_KEY_M))
		mesh_scale(env, param[0]);

	// CAM INTERACTIONS
	// else if (glfwGetKey(window, GLFW_KEY_W) || glfwGetKey(window, GLFW_KEY_A)
	// 	|| glfwGetKey(window, GLFW_KEY_S) || glfwGetKey(window, GLFW_KEY_D)
	// 	|| glfwGetKey(window, GLFW_KEY_R) || glfwGetKey(window, GLFW_KEY_C)
	// 	|| glfwGetKey(window, GLFW_KEY_SPACE))
	// 	cam_translate(env, param[0]);

	// else if (glfwGetKey(window, GLFW_KEY_UP) || glfwGetKey(window, GLFW_KEY_DOWN) \
	// 	|| glfwGetKey(window, GLFW_KEY_LEFT) || glfwGetKey(window, GLFW_KEY_RIGHT) \
	// 	|| glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) || glfwGetKey(window, GLFW_KEY_KP_0))
	// 	cam_look(env, param[0]);


	// DEBUG
	if (glfwGetKey(window, GLFW_KEY_SPACE))
	{
		ft_putendl("\nmodel");
		mat4_print(mat4_transpose(env->world->model));

		ft_putendl("\nview");
		mat4_print(mat4_transpose(env->world->view));

		ft_putendl("\nmodel/view");
		mat4_print(mat4_transpose(mat4_mul(env->world->model, env->world->view)));

		ft_putendl("\nprojection");
		mat4_print(mat4_transpose(env->world->projection));

		ft_putendl("\nmodel/view/projection");
		mat4_print(mat4_transpose(env->world->mvp));
	}

	// fprintf(stdout, "KEYPRESSED!\nkey = %d | scancode = %d | action = %d | mods = %d\n", key, scancode, action, mods);
}
