/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_poly_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:53:25 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/27 15:21:26 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		glfw_poly_mode(int key)
{
	if (key == K_POINTS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	else if (key == K_WIRE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (key == K_POLY)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else
		return (false);
	return (true);
}
