/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_line_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 12:33:53 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/25 11:03:46 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	mesh_line_check(char *str, char *charset)
{
	if (str && charset)
	{
		if ((strspn(str, charset)) != strlen(str))
			return (false);
		else
			return (true);
	}
	return (false);
}
