/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_key_callback.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:36:51 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/08 17:33:36 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	translate(t_scop *env, int key)
{
	if (env)
	{
		if (key == GLFW_KEY_KP_8)
			mat_translate(&env->uni_model_val, vec3f(0.0, 0.01, 0.0));
		else if (key == GLFW_KEY_KP_5)
			mat_translate(&env->uni_model_val, vec3f(0.0, -0.01, 0.0));
		else if (key == GLFW_KEY_KP_4)
			mat_translate(&env->uni_model_val, vec3f(-0.01, 0.0, 0.0));
		else if (key == GLFW_KEY_KP_6)
			mat_translate(&env->uni_model_val, vec3f(0.01, 0.0, 0.0));
		else if (key == GLFW_KEY_KP_7)
			mat_translate(&env->uni_model_val, vec3f(0.0, 0.0, -0.01));
		else if (key == GLFW_KEY_KP_9)
			mat_translate(&env->uni_model_val, vec3f(0.0, 0.0, 0.01));
	}
}

static void	rotate(t_scop *env, int key)
{
	if (env)
	{
		if (key == GLFW_KEY_HOME)
			mat_rotate(&env->uni_model_val, -1, 'x');
		else if (key == GLFW_KEY_END)
			mat_rotate(&env->uni_model_val, 1, 'x');
		else if (key == GLFW_KEY_DELETE)
			mat_rotate(&env->uni_model_val, -1, 'y');
		else if (key == GLFW_KEY_PAGE_DOWN)
			mat_rotate(&env->uni_model_val, 1, 'y');
		else if (key == GLFW_KEY_F13)
			mat_rotate(&env->uni_model_val, -1, 'z');
		else if (key == GLFW_KEY_F15)
			mat_rotate(&env->uni_model_val, 1, 'z');
	}
}

void		glfw_key_callback(GLFWwindow* window, \
						int key, \
						int scancode, \
						int action, \
						int mods)
{
	t_scop	*env;

	env = glfwGetWindowUserPointer(window);
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, 1);

	if (glfwGetKey(window, GLFW_KEY_KP_4) || glfwGetKey(window, GLFW_KEY_KP_5) \
		|| glfwGetKey(window, GLFW_KEY_KP_6) || glfwGetKey(window, GLFW_KEY_KP_7) \
		|| glfwGetKey(window, GLFW_KEY_KP_8) || glfwGetKey(window, GLFW_KEY_KP_9))
		translate(env, key);

	if (glfwGetKey(window, GLFW_KEY_F13) || glfwGetKey(window, GLFW_KEY_F15) \
		|| glfwGetKey(window, GLFW_KEY_HOME) || glfwGetKey(window, GLFW_KEY_DELETE) \
		|| glfwGetKey(window, GLFW_KEY_END) || glfwGetKey(window, GLFW_KEY_PAGE_DOWN))
		rotate(env, key);

	fprintf(stdout, "KEYPRESSED!\n" \
	"key = %d | scancode = %d | action = %d | mods = %d\n",
	key, scancode, action, mods);
}
