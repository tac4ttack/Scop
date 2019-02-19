/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:07:38 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/19 11:44:19 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	exit_ok(void *trash)
{
	if (trash)
		flush((t_scop*)trash);
	glfwTerminate();
	while (1)
		;
	exit(EXIT_SUCCESS);
}

void	exit_fail(const char *msg, void *trash)
{
	if (msg)
		ft_putendl(msg);
	if (trash)
		flush((t_scop*)trash);
	glfwTerminate();
	while (1)
		;
	exit(EXIT_FAILURE);
}
