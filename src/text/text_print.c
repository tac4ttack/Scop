/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 17:27:49 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/27 17:43:50 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	text_print(const char *str, int x, int y, int size)
{
	if (str)
	{
		fprintf(stdout, "text_print() place holder!\n%s\n" \
						"x = %d | y = %d | size = %d\n", str, x, y, size);
		return (true);
	}
	return (false);
}
