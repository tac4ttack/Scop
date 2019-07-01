/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 09:46:27 by fmessina          #+#    #+#             */
/*   Updated: 2019/07/01 11:32:15 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** Project an x,y pair onto a sphere of radius r OR a hyperbolic sheet
** if we are away from the center of the sphere.
*/

static float	input_mouse_porject_to_sphere(float radius, float x, float y)
{
	float d;
	float t;
	float z;

	d = sqrt(x * x + y * y);
	if (d < radius * 0.70710678118654752440)
	{
		z = sqrt(radius * radius - d * d);
	}
	else
	{
		t = radius / 1.41421356237309504880;
		z = t * t / d;
	}
	return (z);
}

void			input_mouse_rot(t_quat *prev, float pos[4])
{
	t_vec3f		axis;
	float		phi;
	float		t;
	t_vec3f		pt[3];

	if ((pos[0] == pos[2]) && (pos[1] == pos[3]))
	{
		*prev = quat_set_identity();
		return ;
	}
	pt[0] = vec3f(pos[0], pos[1], \
			input_mouse_porject_to_sphere(MOUSE_ROT_RADIUS, pos[0], pos[1]));
	pt[1] = vec3f(pos[2], pos[3], \
			input_mouse_porject_to_sphere(MOUSE_ROT_RADIUS, pos[2], pos[3]));
	axis = vec3f_cross(pt[1], pt[0]);
	pt[2] = vec3f_sub(pt[0], pt[1]);
	t = vec3f_len(pt[2]) / (2.0 * MOUSE_ROT_RADIUS);
	if (t > 1.0)
		t = 1.0;
	if (t < -1.0)
		t = -1.0;
	phi = 2.0 * asin(t);
	axis = vec3f_normalize(axis);
	*prev = quat(axis.x * sin((phi / 2)), axis.y * sin((phi / 2)), \
		axis.z * sin((phi / 2)), cos((phi / 2)));
}
