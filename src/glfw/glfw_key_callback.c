/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_key_callback.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:36:51 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/10 14:46:00 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool	translate(t_scop *env, int key)
{
	t_mat4 trans;

	trans = mat4_set_identity();
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
		return (true);
	}
	return (false);
}

static bool	rotate(t_scop *env, int key)
{
	t_mat4 trans;

	trans = mat4_set_identity();
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
		return (true);
	}
	return (false);
}

static bool	scale(t_scop *env, int key)
{
	t_mat4	trans;

	trans = mat4_set_identity();
	if (env)
	{
		if (key == GLFW_KEY_KP_ADD)
			trans = mat4_set_scale(vec3f(1.1f, 1.1f, 1.1f));
		else if (key == GLFW_KEY_KP_SUBTRACT)
			trans = mat4_set_scale(vec3f(0.9f, 0.9f, 0.9f));
		env->mat->scale = mat4_mul(env->mat->scale, trans);
		return (true);
	}
	return (false);
}

static bool		poly_mode(int key)
{
	if (key == GLFW_KEY_1)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	else if (key == GLFW_KEY_2)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (key == GLFW_KEY_3)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else
		return (false);
	return (true);
}

static bool		cam_mode(t_scop *env, int key)
{
	if (env)
	{
		if (key == GLFW_KEY_BACKSLASH)
			env->cam->cam_mod[0] = 45.0f;
		else if (key == GLFW_KEY_APOSTROPHE)
		{
			env->cam->cam_mod[1] = 0.1f;
			env->cam->cam_mod[2] = 100.0f;
		}
		else if (key == GLFW_KEY_LEFT_BRACKET)
			env->cam->cam_mod[0] -= 0.1f;
		else if (key == GLFW_KEY_RIGHT_BRACKET)
			env->cam->cam_mod[0] += 0.1f;
		else if (key == GLFW_KEY_O)
			env->cam->cam_mod[1] += 0.01f;
		else if (key == GLFW_KEY_L)
			env->cam->cam_mod[1] -= 0.01f;
		else if (key == GLFW_KEY_P)
			env->cam->cam_mod[2] += 0.01f;
		else if (key == GLFW_KEY_SEMICOLON)
			env->cam->cam_mod[2] -= 0.01f;
		env->mat->projection = mat4_set(0.0);
		env->mat->projection = mat4_set_perspective(env->cam->cam_mod[0], \
							env->win_res[2], env->cam->cam_mod[1], env->cam->cam_mod[2]);
		return (true);
	}
	return (false);
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

	if (glfwGetKey(window, GLFW_KEY_KP_ADD) \
		|| glfwGetKey(window, GLFW_KEY_KP_SUBTRACT))
		scale(env, param[0]);

	if (glfwGetKey(window, GLFW_KEY_1) || glfwGetKey(window, GLFW_KEY_2) \
		|| glfwGetKey(window, GLFW_KEY_3))
		poly_mode(param[0]);

	if (glfwGetKey(window, GLFW_KEY_BACKSLASH) || glfwGetKey(window, GLFW_KEY_APOSTROPHE) \
		|| glfwGetKey(window, GLFW_KEY_O) || glfwGetKey(window, GLFW_KEY_L) \
		|| glfwGetKey(window, GLFW_KEY_P) || glfwGetKey(window, GLFW_KEY_SEMICOLON)
		|| glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) || glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET))
		cam_mode(env, param[0]);

	// fprintf(stdout, "KEYPRESSED!\nkey = %d | scancode = %d | action = %d | mods = %d\n", key, scancode, action, mods);
}
