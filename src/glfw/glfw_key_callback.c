/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_key_callback.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:36:51 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/10 13:18:07 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	translate(t_scop *env, int key)
{
	t_mat4 trans = mat4_set_identity();

	if (env)
	{
		if (key == GLFW_KEY_KP_8)
			trans = mat4_set_translation(vec3f(0.0, 0.1, 0.0));
		else if (key == GLFW_KEY_KP_5)
			trans = mat4_set_translation(vec3f(0.0, -0.1, 0.0));
		else if (key == GLFW_KEY_KP_4)
			trans = mat4_set_translation(vec3f(-0.1, 0.00, 0.0));
		else if (key == GLFW_KEY_KP_6)
			trans = mat4_set_translation(vec3f(0.1, 0.00, 0.0));
		else if (key == GLFW_KEY_KP_7)
			trans = mat4_set_translation(vec3f(0.0, 0.00, -0.1));
		else if (key == GLFW_KEY_KP_9)
			trans = mat4_set_translation(vec3f(0.0, 0.00, 0.1));
		env->mat->translation = mat4_mul(env->mat->translation, trans);
	}
}

static void	rotate(t_scop *env, int key)
{
	t_mat4 trans = mat4_set_identity();

	if (env)
	{
		if (key == GLFW_KEY_HOME)
			trans = mat4_set_rotation(-1.0, vec3f(1.0, 0.0, 0.0));
		else if (key == GLFW_KEY_END)
			trans = mat4_set_rotation(1.0, vec3f(1.0, 0.0, 0.0));
		else if (key == GLFW_KEY_DELETE)
			trans = mat4_set_rotation(-1.0, vec3f(0.0, 1.0, 0.0));
		else if (key == GLFW_KEY_PAGE_DOWN)
			trans = mat4_set_rotation(1.0, vec3f(0.0, 1.0, 0.0));
		else if (key == GLFW_KEY_F13)
			trans = mat4_set_rotation(-1.0, vec3f(0.0, 0.0, 1.0));
		else if (key == GLFW_KEY_F15)
			trans = mat4_set_rotation(1.0, vec3f(0.0, 0.0, 1.0));
		env->mat->rotation = mat4_mul(env->mat->rotation, trans);
	}
}

void		glfw_key_callback(GLFWwindow* window, \
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
		translate(env, param[0]);

	if (glfwGetKey(window, GLFW_KEY_F13) || glfwGetKey(window, GLFW_KEY_F15) \
		|| glfwGetKey(window, GLFW_KEY_HOME) || glfwGetKey(window, GLFW_KEY_DELETE) \
		|| glfwGetKey(window, GLFW_KEY_END) || glfwGetKey(window, GLFW_KEY_PAGE_DOWN))
		rotate(env, param[0]);

	// fprintf(stdout, "KEYPRESSED!\nkey = %d | scancode = %d | action = %d | mods = %d\n", key, scancode, action, mods);
}
