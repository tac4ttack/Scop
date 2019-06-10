/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:28:09 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/10 14:10:35 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	init_textures(t_scop *env)
{
	t_tga *tga;
	
	if (env)
	{
		if (!(env->texture = ft_memalloc(sizeof(t_texture))))
			return (error_bool("[ERROR init_textures]\t" \
			"Can\'t allocate memory for textures!\n"));
		if (!(tga = tga_load_file(DEFAULT_TEXTURE)))
			return (error_bool("[ERROR init_textures]\t" \
			"Could not load the default Doge texture file!\n"));
			
		env->texture->pixels = ft_memalloc(tga->width * tga->height * 4);
		ft_memcpy(env->texture->pixels, tga->pixels, tga->width * tga->height * 4);

		// if (!(env->texture->pixels = tga_load_file(DEFAULT_TEXTURE))
		// 	return (error_bool("[ERROR init_textures]\t" \
		// 	"Could not load the default Doge texture!\n"));
		env->n_texture = 1;
		return (true);
	}
	return (error_bool("[ERROR init_textures]\tNULL scop pointer!\n"));
}
