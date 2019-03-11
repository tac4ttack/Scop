/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:46:23 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/11 16:53:45 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

/*
**	Custom libs
*/
# include "libft.h"
# include "libftmath.h"
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
# define FOV					45.0
# define NEAR					0.1
# define FAR					100.0

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

	GLfloat						*prepack_vao;
	GLint						*prepack_ebo;

	GLfloat						*vertex;
	size_t						n_vertex[2];

	GLint						*face;
	size_t						n_face[2];

	GLfloat						*normal;
	size_t						n_normal[2];

	GLfloat						*texture;
	size_t						n_texture[2];

	GLfloat						*space;
	size_t						n_space[2];
	double						euler[3];
}								t_mesh;

typedef struct					s_texture
{
	GLuint						id;
	GLuint						*pixels;
	size_t						size[2];
}								t_texture;

typedef struct					s_text2d
{
	GLuint						Text2DVertexBufferID;
	GLuint						Text2DUVBufferID;
	GLuint						Text2DTextureID;
	GLuint						text_shader_program;
	GLuint						Text2DUniformID;
}								t_text2d;

typedef struct 					s_uni
{
	// GLint						time_id;
	GLint						translation_id;
	GLint						rotation_id;
	GLint						scale_id;
	GLint						view_id;
	GLint						projection_id;
}								t_uni;

typedef struct					s_matrix
{
	t_mat4						translation;
	t_mat4						rotation;
	t_mat4						scale;
	t_mat4						view;
	t_mat4						projection;
}								t_matrix;

typedef struct 					s_camera
{
	GLfloat						cam_mod[3];
	t_vec3f						pos;
	t_vec3f						front;
	t_vec3f						up;
	double						euler[3];
	GLfloat						speed;
}								t_camera;

typedef struct					s_keyboard
{
	GLfloat						dummy;
}								t_keyboard;

typedef struct					s_mouse
{
	GLfloat						sensitivity;
	double						last[2];
	bool						ready;
}								t_mouse;

typedef struct					s_scop
{
	GLFWwindow					*win;
	GLsizei						win_res[3];
	GLuint						shader_program;
	GLuint						vbo;
	GLuint						vao;
	GLuint						ebo;
	t_mesh						*mesh;
	char						*mesh_data;
	t_camera					*cam;
	t_keyboard					*key;
	t_matrix					*mat;
	t_mouse						*mouse;
	t_text2d					*text;
	t_texture					*texture;
	size_t						n_texture;
	char						*win_title;
	GLfloat						time_last;
	GLint						time_frames;
	t_uni						*uni;
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
void							glfw_error_callback(const int error, \
													const char *description);
void							glfw_key_callback(GLFWwindow* window, \
													int key, \
													int scancode, \
													int action, \
													int mods);
bool							glfw_launch(t_scop *env);
void							glfw_mouse_button_callback(GLFWwindow *window, \
															int button, \
															int action, \
															int mods);
void							glfw_mouse_pos_callback(GLFWwindow *window, \
														double xpos, \
														double ypos);
void							glfw_mouse_scroll_callback(GLFWwindow *window, \
															double xoffset, \
															double yoffset);
void							glfw_window_size_callback(GLFWwindow *win, \
														const int width, \
														const int height);


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

bool							mesh_prepack(t_mesh *mesh);
bool							mesh_prepack_ebo_data(t_mesh *mesh);
bool							mesh_prepack_vao_data(t_mesh *mesh);

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
void							mesh_print_data_normal(t_mesh *mesh);
void							mesh_print_data_packed_ebo(t_mesh *mesh);
void							mesh_print_data_packed_vao(t_mesh *mesh);
void							mesh_print_data_texture(t_mesh *mesh);
void							mesh_print_data_vertex(t_mesh *mesh);

/*
** Shader functions
*/
bool							shader_build(t_scop *env);
GLuint							shader_uniform_bind(t_scop *env);
GLuint							shader_uniform_update(t_scop *env);

#endif
