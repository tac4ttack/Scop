/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:28:09 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/10 19:26:22 by fmessina         ###   ########.fr       */
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
		if (!(env->texture->pixels = ft_memalloc(tga->n_pix * sizeof(int))))
			return (error_bool("[ERROR init_textures]\t" \
			"Could not allocate memory for texture pixels data!!\n"));
		ft_memcpy(env->texture->pixels, tga->pixels, tga->n_pix * sizeof(int));
		env->texture->size[0] = tga->width;
		env->texture->size[1] = tga->height;
		tga_clean(tga);
		env->n_texture = 1;
		return (true);
	}
	return (error_bool("[ERROR init_textures]\tNULL scop pointer!\n"));
}
