/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:46:23 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/28 17:54:06 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

/*
**	Custom libs
*/
# include "libft.h"
# include "GL/glew.h"
# include "GLFW/glfw3.h"
# include "tga.h"

/*
**	Standard libs
*/
# include <sys/stat.h>	// required for stat()
# include <stdbool.h>	// required for bool type
# include <time.h>		// required for time()
# include <stdio.h>		// required for FILE printf etc
# include <stdarg.h>	// required for va_arg
# include <assert.h>	// required for assert()
# include <fcntl.h>      // required for open()
# include <unistd.h>    // required for read() and close()
# include <string.h>	// required for strspn() used in mesh_line_process_check()
# include <math.h>		// required for sin() etc

# define LOG_FILENAME			"scop.log"

# define DEFAULT_TEXTURE		"./ressources/textures/default.tga"

# define WIDTH					1024
# define HEIGHT					768

# define VERTEX_SHADER_PATH 	"./shaders/simple_vs.glsl"
# define VERTEX_FRAGMENT_PATH 	"./shaders/simple_fs.glsl"

# define CHARSET_V				"v \t.-0123456789"
# define CHARSET_VT				"vt \t.-0123456789"
# define CHARSET_VN				"vn \t.-0123456789"
# define CHARSET_VP				"vp \t.-0123456789"
# define CHARSET_F				 "f \t/-0123456789"
# define CHARSET_L 				"l \t-0123456789"

# define ANTIALIASING			4

# ifdef DEBUG
#  define DEBUG_SCOP			1
# else
#  define DEBUG_SCOP			0
# endif

# ifdef MACOSX
#  define MAC					1
# else
#  define MAC					0
# endif

/*
**	MESH DATA:
**	object		->	object name
**	group		->	object's group name
**	mtllib		->	mtllib specified file
**	usemtl		->	material file specified
**	shading		->	s line boolean
**	vertex		->	vertices array, defined with 4 components
**	n_vertex	->	number of vertices, [0] is preprocessing count,
**					[1] is for checksum and filling
**	face		->	face elements array
**	n_face		->	face elements settings:
**					[0] preprocessing count,
**					[1] checksum control,
**					[2] number of vertices per face element,
**					[3] type of face element definition can take 4 values:
**						0 = Vn | 1 = Vn/VTn | 2 = Vn/VTn/VNn | 3 = Vn//VNn
**					[4] number of values per vertex according to the face format
**					[5] total number to read for a face element definition
**	normal		->	vertices normal array
**	n_normal	->	number of vertices normals:
**					[0] is preprocessing count,
**					[1] is for checksum and filling
**	texture		->	vertices texture coord array
**	n_texture	->	number of vertices texture coord:
**					[0] is preprocessing count,
**					[1] is for checksum and filling
**	space		->	space vertices array
**	n_space		->	number of space vertices:
**					[0] is preprocessing count,
**					[1] is for checksum and filling
**	linel		->	polyline definition array
**	n_line		->	number of polylines:
**					[0] is preprocessing count,
**					[1] is for checksum and filling
*/

typedef struct					s_mesh
{
	char						*object;
	char						*group;
	char						*mtllib;
	char						*usemtl;
	bool						shading;

	GLfloat						*final_vao;

	GLfloat						*vertex;
	size_t						n_vertex[2];

	GLint						*face;
	size_t						n_face[6];
	char						*face_format;

	GLfloat						*normal;
	size_t						n_normal[2];

	GLfloat						*texture;
	size_t						n_texture[2];

	GLfloat						*space;
	size_t						n_space[2];
}								t_mesh;

typedef struct					s_texture
{
	GLuint						id;
	GLuint						*pixels;
	size_t						size[2];
}								t_texture;

typedef struct					s_scop
{
	GLFWwindow					*win;
	GLuint						shader_program;

	t_texture					*texture;
	size_t						n_texture;

	GLuint						vbo;
	GLuint						vao;
	GLuint						ebo;

	t_mesh						*mesh;
	char						*mesh_data;

	GLint						uni_time_id;
	float						uni_time_val;

}								t_scop;

bool							buffer_create(t_scop *env);

void							*error(const char *msg);
bool							error_bool(const char *msg);

void							exit_ok(void *trash);
void							exit_fail(const char *msg, void *trash);

void							flush(t_scop *trash);

void							split_destroy(char **split);
size_t							split_len(char **split);

t_scop							*init(const char *av);

bool							scop_log(const char *message, ...);
bool							scop_log_err(const char *message, ...);
void							scop_log_gl_params(void);
bool							scop_log_restart(void);


/*
** GLFW functions
*/
void							glfw_window_size_callback(GLFWwindow *win, \
														const int width, \
														const int height);
void							glfw_error_callback(const int error, \
													const char *description);
bool							glfw_launch(t_scop *env);


/*
** Mesh functions
*/
void							mesh_clean(t_mesh *mesh);
char							*mesh_file_load(t_scop *env, char *target);
t_mesh							*mesh_file_process(t_scop *env);
bool							mesh_get_face_type(t_mesh *mesh, char *str);
bool							mesh_line_process(t_mesh *mesh, char **split);
bool							mesh_line_process_check(char *str, \
														char *charset);

bool							mesh_line_process_f(t_mesh *mesh, char *str);
bool							mesh_line_process_v(t_mesh *mesh, char *str);
bool							mesh_line_process_vn(t_mesh *mesh, char *str);
bool							mesh_line_process_vp(t_mesh *mesh, char *str);
bool							mesh_line_process_vt(t_mesh *mesh, char *str);

bool							mesh_pack_vao_data(t_mesh *mesh);

bool							mesh_process_face(t_mesh *mesh, char *str);
bool							mesh_process_face_data_dispatch(t_mesh *mesh, \
																char *str, \
																int mod, \
																int index);
bool							mesh_process_face_quad(t_mesh *mesh, \
														char **split, \
														int index);
bool							mesh_process_face_triangle(t_mesh *mesh, \
														char **split, \
														int index);
int								mesh_process_face_type_get(char *sample);
bool							mesh_process_normal(t_mesh *mesh, char *str);
bool							mesh_process_space(t_mesh *mesh, char *str);
bool							mesh_process_texture(t_mesh *mesh, char *str);
bool							mesh_process_vertex(t_mesh *mesh, char *str);

void							mesh_print_data(t_mesh *mesh);
void							mesh_print_data_face(t_mesh *mesh);
void							mesh_print_data_face_type(t_mesh *mesh);
void							mesh_print_data_normal(t_mesh *mesh);
void							mesh_print_data_texture(t_mesh *mesh);
void							mesh_print_data_vertex(t_mesh *mesh);

/*
** Shader functions
*/
bool							shader_build(t_scop *env);
GLuint							shader_uniform_bind(t_scop *env);
GLuint							shader_uniform_update(t_scop *env);

#endif
