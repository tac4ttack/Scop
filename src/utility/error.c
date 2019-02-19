/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 16:05:46 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/19 11:09:49 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"



bool    error_bool(const char *msg)
{
    if (msg)
        ft_putendl(msg);
    return (false);
}

void    *error(const char *msg)
{
    if (msg)
        ft_putendl(msg);
    return NULL;
}
