/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 10:35:08 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/18 10:36:48 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_dmat4 *mat_init(t_dmat4 *matrix, const size_t col, const size_t row)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (matrix)
	{
		while (j < col)
		{
			while (i < row)
			{
				matrix->p[j][i] = 0.0f;
				i++;
			}
			j++;
		}
		return (matrix);
	}
	else
		return (NULL);
}
