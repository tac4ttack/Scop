/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:46:23 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/24 17:28:21 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

/*
**	Custom libs
*/
# include "libft.h"
# include "libftmath.h"
# include "simpleOBJ.h"
# include "simpleTGA.h"

/*
**	OpenGL related libs
*/
# include "GL/glew.h"
# include "GLFW/glfw3.h"

/*
**	Standard libs
*/
# include <stdbool.h>	// required for bool type
# include <stdio.h>		// required for FILE printf etc
# include <string.h>	// required for strspn() used in mesh_line_process_check()
# include <math.h>		// required for sin() etc

# define SCOP_LOG_FILENAME		"scop.log"

# define DEFAULT_TEXTURE		"./ressources/textures/default.tga"

# define WIDTH					1024
# define HEIGHT					768
# define FOV					45.0
# define NEAR					0.1
# define FAR					100.0

# define VERTEX_SHADER_PATH 	"./shaders/simple_vs.glsl"
# define VERTEX_FRAGMENT_PATH 	"./shaders/simple_fs.glsl"


# define ANTIALIASING			4

# define VAOLEN				14

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
**	TEXTURES DATA STRUCT:
**	---------------------
*/
typedef struct					s_texture
{
	GLuint						id;
	GLuint						*pixels;
	size_t						size[2];
}								t_texture;

/*
**	BITMAP FONT STRUCT:
**	-------------------
*/
typedef struct					s_text2d
{
	GLuint						Text2DVertexBufferID;
	GLuint						Text2DUVBufferID;
	GLuint						Text2DTextureID;
	GLuint						text_shader_program;
	GLuint						Text2DUniformID;
}								t_text2d;

/*
**	OPENGL UNIFORMS STRUCT:
**	-----------------------
*/
typedef struct 					s_uni
{
	GLint						mvp_id;
}								t_uni;

/*
**	WORLD STRUCT:
**	--------------
**	cam_mod stores camera settings
**	cam_mod[0] = FOV
**	cam_mod[1] = NEAR
**	cam_mod[2] = FAR
*/
typedef struct 					s_world
{
	double						cam_euler[3];
	GLfloat						cam_mod[3];
	t_vec3f						cam_position;
	t_quat						cam_orientation;
	t_vec3f						cam_front;
	t_vec3f						cam_up;
	t_vec3f						cam_right;
	GLfloat						cam_speed;

	double						mesh_euler[3];
	t_vec3f						mesh_position;
	t_mat4						mesh_translation;
	t_quat						mesh_orient;
	t_mat4						mesh_rotation;

	t_vec3f						mesh_scaler;
	t_mat4						mesh_scale;


	t_mat4						model;
	t_mat4						view;
	t_mat4						projection;
	t_mat4						mvp;

	t_vec3f						world_up;
}								t_world;


/*
**	KEYBOARD INPUTS STRUCT:
**	-----------------------
*/
typedef struct					s_keyboard
{
	GLfloat						dummy;
}								t_keyboard;

/*
**	MOUSE INPUT STRUCT:
**	-------------------
*/
typedef struct					s_mouse
{
	GLfloat						sensitivity;
	double						last[2];
	bool						ready;
}								t_mouse;

/*
**	SCOP STRUCT:
**	------------
**	This is the core data structure of this program
**
**	The VAO OpenGL buffer will contain for each vertex the following data:
**	vao[index + 0]	= vertex position X
**	vao[index + 1]	= vertex position Y 
**	vao[index + 2]	= vertex position Z
**	vao[index + 3]	= vertex position W
**	vao[index + 4]	= vertex Alpha color channel   // NEED TO CHECK THE CORRECT FORMAT USED 
**	vao[index + 5]	= vertex Red color channel
**	vao[index + 6]	= vertex Green color channel
**	vao[index + 7]	= vertex Blue color channel
**	vao[index + 8]	= vertex texture U coordinate
**	vao[index + 9]	= vertex texture V coordinate
**	vao[index + 10]	= vertex texture W coordinate
**	vao[index + 11]	= vertex normal parameter I
**	vao[index + 12]	= vertex normal parameter J
**	vao[index + 13]	= vertex normal parameter K
**
**	The EBO OpenGL buffer will contains all vertices index needed to build faces
**
*/
typedef struct					s_scop
{
	GLFWwindow					*win;
	GLsizei						win_res[3];
	char						*win_title;

	GLuint						shader_program;
	t_uni						*uni;

	GLuint						vbo;
	
	GLuint						vao;
	size_t						vao_len;
	GLfloat						*prepack_vao;
	
	GLuint						ebo;
	GLint						*prepack_ebo;

	t_obj						*mesh;

	t_world						*world;

	t_keyboard					*key;
	t_mouse						*mouse;

	t_text2d					*text;

	t_texture					*texture;
	size_t						n_texture;

	GLfloat						time_last;
	GLfloat						time_delta;
	GLint						time_frames;

}								t_scop;

bool							buffer_create(t_scop *env);

/*
**	CALLBACK Functions
*/
void							cb_error(const int error, \
										const char *description);
void							cb_keyboard(GLFWwindow* window, \
											int key, \
											int scancode, \
											int action, \
											int mods);
void							cb_framebuffer_size(GLFWwindow* window, \
													int width, \
													int height);
void							cb_mouse_btn(GLFWwindow *window, \
											int button, \
											int action, \
											int mods);
void							cb_mouse_pos(GLFWwindow *window, \
											double xpos, \
											double ypos);
void							cb_mouse_scroll(GLFWwindow *window, \
												double xoffset, \
												double yoffset);
void							cb_window_size(GLFWwindow *win, \
												const int width, \
												const int height);

/*
**	INIT Functions
*/
t_scop							*init(const char *av);
bool							init_glew(t_scop *env);
bool							init_glfw(t_scop *env);
bool							init_keyboard(t_scop *env);
bool							init_mouse(t_scop *env);
bool							init_textures(t_scop *env);
bool							init_uniforms(t_scop *env);
bool							init_world(t_scop *env);

/*
**	UTILITY Functions
*/
void							*error(const char *msg);
bool							error_bool(const char *msg);
void							exit_ok(void *trash);
void							exit_fail(const char *msg, void *trash);
void							flush(t_scop *trash);
void							split_destroy(char **split);
size_t							split_len(char **split);
bool							time_update(t_scop *env);

/*
**	SCOP LOGGING Functions
*/
bool							scop_log(const char *message, ...);
bool							scop_log_err(const char *message, ...);
void							scop_log_gl_params(void);
bool							scop_log_restart(void);


/*
** GLFW Functions
*/
bool							glfw_clean(t_scop *env);
bool							glfw_main_loop(t_scop *env);
bool							glfw_poly_mode(int key);

/*
** MESH Functions
*/
bool							mesh_prepack(t_scop *env);
bool							mesh_prepack_center_vertices(t_obj *mesh);
bool							mesh_prepack_ebo_data(t_scop *env);
bool							mesh_prepack_get_center_axis(t_obj *mesh);
bool							mesh_prepack_vao_data(t_scop *env);
void							mesh_print_data_packed_ebo(t_scop* env);
void							mesh_print_data_packed_vao(t_scop* env);
bool							mesh_rotate_self(t_scop *env, int key);
bool							mesh_scale(t_scop *env, int key);
bool							mesh_translate(t_scop *env, int key);

/*
** SHADER Functions
*/
bool							shader_build(t_scop *env);
GLuint							shader_uniform_bind(t_scop *env);
GLuint							shader_uniform_update(t_scop *env);

/*
** WORLD Functions
*/
bool							world_update(t_scop *env);
#endif
