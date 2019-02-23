/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:46:23 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/23 17:54:53 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

// STANDARD LIBS
// # include <stdlib.h>
// # include <unistd.h>
// # include <math.h>

// # include <fcntl.h>

// // GL_LOG SHIT
// # include <stdarg.h>


// CUSTOM LIBS
# include "libft.h"
# include "GL/glew.h"
# include "GLFW/glfw3.h"

// PROJECT INCLUDES
# include <sys/stat.h>	// required for stat()
# include <stdbool.h>	// required for bool type
# include <time.h>		// required for time()
# include <stdio.h>		// required for FILE printf etc
# include <stdarg.h>	// required for va_arg
# include <assert.h>	// required for assert()
# include <fcntl.h>      // required for open()
# include <unistd.h>    // required for read() and close()
# include <string.h>	// required for strspn() used in mesh_line_check()

# define LOG_FILENAME "scop.log"

# define WIDTH 1024
# define HEIGHT 768

# define VERTEX_SHADER_PATH "./shaders/simple_vs.glsl"
# define VERTEX_FRAGMENT_PATH "./shaders/simple_fs.glsl"

# define CHARSET_V "v \t.-0123456789"
# define CHARSET_VT "vt \t.-0123456789"
# define CHARSET_VN "vn \t.-0123456789"
# define CHARSET_VP "vp \t.-0123456789"
# define CHARSET_F "f \t/-0123456789"
# define CHARSET_L "l \t-0123456789"

# ifdef DEBUG
#  define DEBUG_SCOP					1
# else
#  define DEBUG_SCOP					0
# endif

# ifdef MACOSX
#	define MAC 1
# else
#  define MAC 0
# endif

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef struct	s_vec4
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec4;

/*
**	MESH DATA:
**	object		->	object name
**	group		->	object's group name
**	mtllib		->	mtllib specified file
**	usemtl		->	material file specified
**	shading		->	s line boolean
**	vertex		->	vertices array, defined with 4 components
**	n_vertex	->	number of vertices, [0] is preprocessing count, [1] is for checksum and filling
**	face		->	face elements array
**	n_face		->	face elements settings, [0] is preprocessing count, [1] is for checksum,
**					[2] is the number of vertices per face element,
**					[3] if the type of face element definition, can take 4 values:
**						0 = Vn | 1 = Vn/VTn | 2 = Vn/VTn/VNn | 3 = Vn//VNn
**					[4] is the number of values per vertex according to the face format
**					[5] is the total number to read for a face element definition
**	normal		->	vertices normal array
**	n_normal	-> number of vertices normals, [0] is preprocessing count, [1] is for checksum and filling
**	texture		->	vertices texture coord array
**	n_texture	-> number of vertices texture coord, [0] is preprocessing count, [1] is for checksum and filling
**	space		->	space vertices array
**	n_space		-> number of space vertices, [0] is preprocessing count, [1] is for checksum and filling
**	linel		->	polyline definition array
**	n_line		-> number of polylines, [0] is preprocessing count, [1] is for checksum and filling
*/

typedef struct	s_mesh
{
	char		*object;
	char		*group;
	char		*mtllib;
	char		*usemtl;
	bool		shading;

	GLfloat		*vertex;
	size_t		n_vertex[2];

	GLint		*face;
	size_t		n_face[6];
	char		*face_format;

	GLfloat		*normal;
	size_t		n_normal[2];

	GLfloat		*texture;
	size_t		n_texture[2];

	GLfloat		*space;
	size_t		n_space[2];

	GLint		*line;
	size_t		n_line[2];
}				t_mesh;

typedef struct	s_scop
{
	GLFWwindow	*win;
	GLuint		shader_program;

	GLuint		vbo;
	GLuint		vao;
	GLuint		ebo;

	GLint		uniform_test; // for testing purpose!
	int			uniform_test_value; // for testing purpose!

	t_mesh		*mesh;
	char		*mesh_data;
}				t_scop;

bool			buffer_create(t_scop *env);

void			*error(const char *msg);
bool			error_bool(const char *msg);

void			exit_ok(void *trash);
void			exit_fail(const char *msg, void *trash);

void			flush(t_scop *trash);
void			split_destroy(char **split);

t_scop			*init(const char *av);

bool			scop_log(const char *message, ...);
bool			scop_log_err(const char *message, ...);
void			scop_log_gl_params(void);
bool			scop_log_restart(void);

void			glfw_window_size_callback(GLFWwindow *win, \
									const int width, \
									const int height);
void			glfw_error_callback(const int error, const char *description);
bool			glfw_launch(t_scop *env);

void			mesh_clean(t_mesh *mesh);
char			*mesh_file_load(t_scop *env, const char *target);
t_mesh			*mesh_file_process(t_scop *env);
bool			mesh_get_face_type(t_mesh *mesh, char *str);
bool			mesh_line_check(char *str, char *charset);
bool			mesh_line_process(t_mesh *mesh, char **split);
bool			mesh_line_process_face(t_mesh *mesh, char *str);
bool			mesh_process_face(t_mesh *mesh, \
									// char *format,
									char **split, \
									size_t index);
bool			mesh_line_process_vertex(t_mesh *mesh, char *str);
void			mesh_print_data(t_mesh *mesh);
void			mesh_print_data_face(t_mesh *mesh);
void			mesh_print_data_face_type(t_mesh *mesh);
void			mesh_print_data_vertex(t_mesh *mesh);

bool			shader_build(t_scop *env);
GLuint			shader_uniform_bind(t_scop *env);
GLuint			shader_uniform_update(t_scop *env);

#endif
