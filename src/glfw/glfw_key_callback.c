/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_key_callback.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:36:51 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/11 18:41:46 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool	mesh_translate(t_scop *env, int key)
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
		else if (key == GLFW_KEY_KP_9)
			trans = mat4_set_translation(vec3f(0.0, 0.00, -0.1));
		else if (key == GLFW_KEY_KP_7)
			trans = mat4_set_translation(vec3f(0.0, 0.00, 0.1));
		env->mat->translation = mat4_mul(env->mat->translation, trans);
		return (true);
	}
	return (false);
}

static bool	mesh_self_rotate(t_scop *env, int key)
{
	if (env)
	{
		if (key == GLFW_KEY_HOME)
			env->mesh->euler[0] += 1.0;
		else if (key == GLFW_KEY_END)
			env->mesh->euler[0] -= 1.0;
		else if (key == GLFW_KEY_DELETE)
			env->mesh->euler[1] += 1.0;
		else if (key == GLFW_KEY_PAGE_DOWN)
			env->mesh->euler[1] -= 1.0;
		else if (key == GLFW_KEY_F13)
			env->mesh->euler[2] += 1.0;
		else if (key == GLFW_KEY_F15)
			env->mesh->euler[2] -= 1.0;
		env->mesh->euler[0] = (env->mesh->euler[0] < 0.0 ? 359.0 : env->mesh->euler[0]);
		env->mesh->euler[0] = (env->mesh->euler[0] > 360.0 ? 1.0 : env->mesh->euler[0]);
		env->mesh->euler[1] = (env->mesh->euler[1] < 0.0 ? 359.0 : env->mesh->euler[1]);
		env->mesh->euler[1] = (env->mesh->euler[1] > 360.0 ? 1.0 : env->mesh->euler[1]);
		env->mesh->euler[2] = (env->mesh->euler[2] < 0.0 ? 359.0 : env->mesh->euler[2]);
		env->mesh->euler[2] = (env->mesh->euler[2] > 360.0 ? 1.0 : env->mesh->euler[2]);
		env->mat->rotation = quat_2_mat4(quat_euler(env->mesh->euler[0], \
								env->mesh->euler[1], env->mesh->euler[2]));
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

static bool	cam_translate(t_scop *env, int key)
{
	if (env)
	{
		if (key == GLFW_KEY_R)
			env->cam->pos = vec3f(0.0f, 0.0f, 0.0f);
		else if (key == GLFW_KEY_W)
			env->cam->pos = vec3f_add(env->cam->pos, \
							vec3f_mul_scalar(env->cam->front, env->cam->speed));
		else if (key == GLFW_KEY_S)
			env->cam->pos = vec3f_sub(env->cam->pos, \
							vec3f_mul_scalar(env->cam->front, env->cam->speed));
		else if (key == GLFW_KEY_A)
			env->cam->pos = vec3f_sub(env->cam->pos, vec3f_mul_scalar( \
				vec3f_normalize(vec3f_cross(env->cam->front, env->cam->up)), \
				env->cam->speed));
		else if (key == GLFW_KEY_D)
			env->cam->pos = vec3f_add(env->cam->pos, vec3f_mul_scalar( \
				vec3f_normalize(vec3f_cross(env->cam->front, env->cam->up)), \
				env->cam->speed));
		else if (key == GLFW_KEY_SPACE)
			;
		else if (key == GLFW_KEY_C)
			;
		env->mat->view = mat4_set_lookat(env->cam->pos, \
					vec3f_add(env->cam->pos, env->cam->front), env->cam->up);
		return (true);
	}
	return (false);
}

static bool	cam_look(t_scop *env, int key)
{
	// totally broken!
	if (env)
	{
		if (key == GLFW_KEY_UP)
			env->cam->euler[0] += 1.0;
		else if (key == GLFW_KEY_DOWN)
			env->cam->euler[0] -= 1.0;
		else if (key == GLFW_KEY_LEFT)
			env->cam->euler[1] += 1.0;
		else if (key == GLFW_KEY_RIGHT)
			env->cam->euler[1] -= 1.0;
		else if (key == GLFW_KEY_RIGHT_CONTROL)
			env->cam->euler[2] += 1.0;
		else if (key == GLFW_KEY_RIGHT)
			env->cam->euler[2] -= 1.0;
		env->cam->euler[0] = (env->cam->euler[0] <= 0.0 ? 359.0 : env->cam->euler[0]);
		env->cam->euler[0] = (env->cam->euler[0] >= 360.0 ? 1.0 : env->cam->euler[0]);
		env->cam->euler[1] = (env->cam->euler[1] <= 0.0 ? 359.0 : env->cam->euler[1]);
		env->cam->euler[1] = (env->cam->euler[1] >= 360.0 ? 1.0 : env->cam->euler[1]);
		env->cam->euler[2] = (env->cam->euler[2] <= 0.0 ? 359.0 : env->cam->euler[2]);
		env->cam->euler[2] = (env->cam->euler[2] >= 360.0 ? 1.0 : env->cam->euler[2]);

		env->cam->front = vec3f_normalize(mat4_on_vec3f(quat_2_mat4(quat_euler(env->cam->euler[0], \
						env->cam->euler[1], env->cam->euler[2])), env->cam->front));
		env->mat->view = mat4_set_lookat(env->cam->pos, env->cam->front, env->cam->up);
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
		mesh_translate(env, param[0]);

	else if (glfwGetKey(window, GLFW_KEY_F13) || glfwGetKey(window, GLFW_KEY_F15) \
		|| glfwGetKey(window, GLFW_KEY_HOME) || glfwGetKey(window, GLFW_KEY_DELETE) \
		|| glfwGetKey(window, GLFW_KEY_END) || glfwGetKey(window, GLFW_KEY_PAGE_DOWN))
		mesh_self_rotate(env, param[0]);

	else if (glfwGetKey(window, GLFW_KEY_KP_ADD) \
		|| glfwGetKey(window, GLFW_KEY_KP_SUBTRACT))
		scale(env, param[0]);

	else if (glfwGetKey(window, GLFW_KEY_1) || glfwGetKey(window, GLFW_KEY_2) \
		|| glfwGetKey(window, GLFW_KEY_3))
		poly_mode(param[0]);

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
