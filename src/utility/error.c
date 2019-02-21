/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 16:05:46 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/21 13:09:35 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"



bool    error_bool(const char *msg)
{
    if (msg)
        scop_log(msg);
    return (false);
}

void    *error(const char *msg)
{
    if (msg)
        scop_log(msg);
    return NULL;
}
