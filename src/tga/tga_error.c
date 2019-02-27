/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 11:03:00 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/27 11:38:41 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	*tga_error(const char *message, void *trash)
{
	if (trash)
	{
		free(trash);
		trash = NULL;
	}
	fprintf(stderr, "TGA Loading error: %s\n", message);
	return (NULL);
}
