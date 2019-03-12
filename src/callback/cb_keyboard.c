/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_keyboard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:35:13 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/12 10:56:48 by fmessina         ###   ########.fr       */
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
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, 1);

	if (glfwGetKey(window, GLFW_KEY_KP_4) || glfwGetKey(window, GLFW_KEY_KP_5) \
		|| glfwGetKey(window, GLFW_KEY_KP_6) || glfwGetKey(window, GLFW_KEY_KP_7) \
		|| glfwGetKey(window, GLFW_KEY_KP_8) || glfwGetKey(window, GLFW_KEY_KP_9))
		mesh_translate(env, param[0]);

	else if (glfwGetKey(window, GLFW_KEY_F13) || glfwGetKey(window, GLFW_KEY_F15) \
		|| glfwGetKey(window, GLFW_KEY_HOME) || glfwGetKey(window, GLFW_KEY_DELETE) \
		|| glfwGetKey(window, GLFW_KEY_END) || glfwGetKey(window, GLFW_KEY_PAGE_DOWN))
		mesh_rotate_self(env, param[0]);

	else if (glfwGetKey(window, GLFW_KEY_KP_ADD) \
		|| glfwGetKey(window, GLFW_KEY_KP_SUBTRACT))
		mesh_scale(env, param[0]);

	else if (glfwGetKey(window, GLFW_KEY_1) || glfwGetKey(window, GLFW_KEY_2) \
		|| glfwGetKey(window, GLFW_KEY_3))
		glfw_poly_mode(param[0]);

	else if (glfwGetKey(window, GLFW_KEY_W) || glfwGetKey(window, GLFW_KEY_A)
		|| glfwGetKey(window, GLFW_KEY_S) || glfwGetKey(window, GLFW_KEY_D)
		|| glfwGetKey(window, GLFW_KEY_R) || glfwGetKey(window, GLFW_KEY_C)
		|| glfwGetKey(window, GLFW_KEY_SPACE))
		cam_translate(env, param[0]);

	else if (glfwGetKey(window, GLFW_KEY_UP) || glfwGetKey(window, GLFW_KEY_DOWN) \
		|| glfwGetKey(window, GLFW_KEY_LEFT) || glfwGetKey(window, GLFW_KEY_RIGHT) \
		|| glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) || glfwGetKey(window, GLFW_KEY_KP_0))
		cam_look(env, param[0]);

	// fprintf(stdout, "KEYPRESSED!\nkey = %d | scancode = %d | action = %d | mods = %d\n", key, scancode, action, mods);
}
