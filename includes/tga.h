
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_tga_parser.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 12:08:50 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/15 17:58:29 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TGA_H
# define TGA_H

// # include <stdlib.h>    // required for NULL size_t exit bidule
// # include <sys/stat.h>   // required for stat()
// # include <fcntl.h>      // required for open()
// # include <unistd.h>    // required for read()
// # include <stdio.h>     // required for printf()
// # include <string.h>    // required for bzero()


# ifdef DEBUG
#  define DEBUG_TGA 1
# else
#  define DEBUG_TGA	0
# endif

# define TGA_TYPE_NODATA 0
# define TGA_TYPE_RAW_CM 1
# define TGA_TYPE_RAW_TC 2
# define TGA_TYPE_RAW_BW 3
# define TGA_TYPE_RLE_CM 9
# define TGA_TYPE_RLE_TC 10
# define TGA_TYPE_RLE_BW 11

# define TGA_IMG_ORI_BL 0
# define TGA_IMG_ORI_BR 1
# define TGA_IMG_ORI_TL 2
# define TGA_IMG_ORI_TR 3

// Pragma required to disable padding in next structure
# pragma pack(push, 1)
typedef struct			s_tga_header
{
	char				id_length;
	char				color_map_type;
	char				image_type;
	unsigned short		first_entry_index;
	unsigned short		color_map_length;
	unsigned char		color_map_entry_size;
	unsigned short		x_origin;
	unsigned short		y_origin;
	unsigned short		image_width;
	unsigned short		image_heigth;
	unsigned char		pixel_depth;
	unsigned char		image_descriptor;
	// char				end_padding[3];	// inutile si pragma pack?
}						t_tga_header;

# pragma pack(pop)

typedef struct 			s_tga_info
{
	void				*data;
	unsigned int		*pixels;
	t_tga_header		*header;
	size_t				file_size;
	size_t				pixels_nbytes;
	unsigned short		image_origin;
	size_t				depth;
	size_t				width;
	size_t				height;
	unsigned short		image_attributes;
	int					extension_offset;
	int					developer_offset;
	char				*signature;
	char				*id;
}						t_tga_info;


//	TGA parsing functions
void					*tga_error(const char *message, void *trash);

unsigned int			*tga_load_file(const char *target, \
										size_t *width, \
										size_t *height);

void					*tga_process_file(const char *target, \
											size_t *target_size);

unsigned int			*tga_process_pixels(t_tga_info *tga, \
											size_t *width, \
											size_t *height);

// void 					tga_process_pixels_32(unsigned int *buffer, \
// 												size_t length);

#endif
