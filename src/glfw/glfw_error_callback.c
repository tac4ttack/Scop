/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_error_callback.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 11:44:02 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/18 16:23:26 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	glfw_error_callback(const int error, const char *description)
{
	scop_log_err("GLFW ERROR: code %i msg:\n%s\n", error, description);
}
