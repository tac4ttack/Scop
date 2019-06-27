/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_keyboard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:35:13 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/27 16:13:00 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	keyboard_mesh_translate_scale_keys(t_scop *env, int *param)
{
	bool	check;

	check = (param[2] == GLFW_PRESS || param[2] == GLFW_REPEAT);
	if (env && env->key)
	{
		if (param[0] == K_TRA_BC)
			env->key->key_q = check;
		if (param[0] == K_TRA_UP)
			env->key->key_w = check;
		if (param[0] == K_TRA_FR)
			env->key->key_e = check;
		if (param[0] == K_TRA_LT)
			env->key->key_a = check;
		if (param[0] == K_TRA_DN)
			env->key->key_s = check;
		if (param[0] == K_TRA_RT)
			env->key->key_d = check;
		if (param[0] == K_SCA_DN)
			env->key->key_lbra = check;
		if (param[0] == K_SCA_UP)
			env->key->key_rbra = check;
	}
}

static void	keyboard_mesh_rotate_keys(t_scop *env, int *param)
{
	bool	check;

	check = (param[2] == GLFW_PRESS || param[2] == GLFW_REPEAT);
	if (env && env->key)
	{
		if (param[0] == K_ROT_NZ)
			env->key->key_u = check;
		else if (param[0] == K_ROT_PX)
			env->key->key_i = check;
		else if (param[0] == K_ROT_PZ)
			env->key->key_o = check;
		else if (param[0] == K_ROT_NY)
			env->key->key_j = check;
		else if (param[0] == K_ROT_NX)
			env->key->key_k = check;
		else if (param[0] == K_ROT_PY)
			env->key->key_l = check;
		else if (param[0] == K_AUTO_ROT_DN)
			env->key->key_autorot_minus = check;
		else if (param[0] == K_AUTO_ROT)
			env->key->key_autorot = check;
		else if (param[0] == K_AUTO_ROT_UP)
			env->key->key_autorot_plus = check;
	}
}

static void	keyboard_options_key(t_scop *env, int *param)
{
	bool	check;

	check = (param[2] == GLFW_PRESS || param[2] == GLFW_REPEAT);
	if (env && env->key)
	{
		if (param[0] == K_POLY)
			env->key->key_poly = check;
		else if (param[0] == K_WIRE)
			env->key->key_wire = check;
		else if (param[0] == K_POINTS)
			env->key->key_points = check;
		else if (param[0] == K_SHADING)
			env->key->key_shading = check;
		else if (param[0] == K_DESATURATE)
			env->key->key_desaturate = check;
		else if (param[0] == K_TEXTU_DEF)
			env->key->key_texture_default = check;
		else if (param[0] == K_TEXTU_MESH)
			env->key->key_texture_mesh = check;
		else if (param[0] == K_UV_MODE)
			env->key->key_uv_mode = check;
		else if (param[0] == K_COLORIZE)
			env->key->key_colorize = check;
	}
}

static void	keyboard_process_no_repeat(t_scop *env, int key)
{
	if (env && env->key)
	{
		if (key == K_AUTO_ROT && !env->key->key_autorot)
			env->auto_rot = !env->auto_rot;
		if (key == K_SHADING && !env->key->key_shading)
			env->smooth_shading = !env->smooth_shading;
		if (key == K_DESATURATE && !env->key->key_desaturate)
			input_cycle_desaturate(env);
		if (key == K_TEXTU_DEF && !env->key->key_texture_default)
			env->texture_default = !env->texture_default;
		if (key == K_TEXTU_MESH && !env->key->key_texture_mesh)
			env->colorize = !env->colorize;
		if (key == K_UV_MODE && !env->key->key_uv_mode)
			env->mesh_uv = !env->mesh_uv;
		if (key == K_COLORIZE && !env->key->key_colorize)
			env->colorize = !env->colorize;
		if ((key == K_POINTS && !env->key->key_poly)
			|| (key == K_WIRE && !env->key->key_wire)
			|| (key == K_POLY && !env->key->key_points))
			glfw_poly_mode(key);
	}
}

void		cb_keyboard(GLFWwindow *win, \
						int key, \
						int scancode, \
						int action)
{
	int		param[4];
	t_scop	*env;

	env = glfwGetWindowUserPointer(win);
	param[0] = key;
	param[1] = scancode;
	param[2] = action;
	keyboard_mesh_translate_scale_keys(env, (int*)&param);
	keyboard_mesh_rotate_keys(env, (int*)&param);
	keyboard_options_key(env, (int*)&param);
	keyboard_process_no_repeat(env, param[0]);
	if ((GLFW_PRESS == glfwGetKey(win, GLFW_KEY_ESCAPE)))
		glfwSetWindowShouldClose(win, 1);
	if (param[0] == K_RESET && param[2] == GLFW_PRESS)
		mesh_reset(env);
}
