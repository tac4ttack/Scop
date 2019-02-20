/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:46:23 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/20 18:40:12 by fmessina         ###   ########.fr       */
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

# define LOG_FILENAME "scop.log"
# define WIDTH 1024
# define HEIGHT 768
# define VERTEX_SHADER_PATH "./shaders/simple_vs.glsl"
# define VERTEX_FRAGMENT_PATH "./shaders/simple_fs.glsl"

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

typedef struct	s_mesh
{
	GLfloat		*vertex;
	size_t		n_vertex;
	int			*face;
	size_t		n_face;
	short int	n_face_vertex;
}				t_mesh;

typedef struct	s_scop
{
	GLFWwindow	*win;
	GLuint		shader_program;

	GLuint		vbo;
	GLuint		vao;

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

char			*mesh_file_load(t_scop *env, const char *target);
t_mesh			*mesh_file_process(t_scop *env);
bool			mesh_line_process(t_mesh *mesh, char **split);
bool			mesh_line_process_face(t_mesh *mesh, char *str);
bool			mesh_line_process_vertex(t_mesh *mesh, char *str);
void			mesh_print_data(t_mesh *mesh);

bool			shader_build(t_scop *env);
GLuint			shader_uniform_bind(t_scop *env);
GLuint			shader_uniform_update(t_scop *env);




////////////////////
// PLAYGROUND
void temp_error(char *str);
bool restart_gl_log();
bool gl_log(const char *message, ...);
bool gl_log_err(const char *message, ...);
void gl_log_params();

// # define DESTROYNOTIFY			17
// # define KEYPRESSMASK			(1L<<0)
// # define KEYRELEASEMASK			(1L<<1)
// # define KEYPRESS				2
// # define KEYRELEASE				3

// # define DEG2RAD				(M_PI / 180)
// # define RAD2DEG				(180 / M_PI)

// # define WIDTH					e->scene->win_w
// # define HEIGHT					e->scene->win_h
// # define DEPTH					e->scene->depth

// # define KRT					e->kernel_rt
// # define NCAM					e->scene->n_cams
// # define NCON					e->scene->n_cones
// # define NCYL					e->scene->n_cylinders
// # define NLIG					e->scene->n_lights
// # define NPLA					e->scene->n_planes
// # define NSPH					e->scene->n_spheres
// # define ACTIVEOBJ				e->target_obj
// # define CAM					e->cameras
// # define CONES					e->cones
// # define CYLIND					e->cylinders
// # define LIGHT					e->lights
// # define PLANE					e->planes
// # define SPHERE					e->spheres
// # define ACTIVECAM				e->cameras[e->scene->active_cam]

// # define XMLSUB					e->xml->sub_node
// # define XML					e->xml
// # define SCN					e->scene

// # define OPTION_WAVE			(1 << 1)
// # define OPTION_SEPIA			(1 << 2)
// # define OPTION_BW				(1 << 3)

// typedef struct			s_fps
// {
// 	struct timeval		step2;
// 	struct timeval		step;
// 	struct timeval		cur;
// 	float				delta_time;
// 	float				u_time;
// 	unsigned int		fps;
// 	unsigned int		ret_fps;
// }						t_fps;

// typedef struct			s_p2i
// {
// 	int					x;
// 	int					y;
// }						t_p2i;

// typedef struct			s_hit
// {
// 	float				dist;
// 	int					type;
// 	int					id;
// 	cl_float3			pos;
// 	cl_float3			normale;
// }						t_hit;

// typedef struct			s_cam
// {
// 	cl_float3			pos;
// 	cl_float3			dir;
// 	cl_float			fov;
// 	cl_float			pitch;
// 	cl_float			yaw;
// 	cl_float			roll;
// }						t_cam;

// typedef struct			s_cone
// {
// 	cl_float3			pos;
// 	cl_float3			dir;
// 	cl_float			angle;
// 	cl_int				color;
// 	cl_float3			diff;
// 	cl_float3			spec;
// 	cl_float			reflex;
// }						t_cone;

// typedef struct			s_cylinder
// {
// 	cl_float3			pos;
// 	cl_float3			dir;
// 	cl_float3			base_dir;
// 	cl_float			radius;
// 	cl_int				color;
// 	cl_float			height;
// 	cl_float3			diff;
// 	cl_float3			spec;
// 	cl_float			pitch;
// 	cl_float			yaw;
// 	cl_float			roll;
// 	cl_float			reflex;
// }						t_cylinder;

// typedef struct			s_light
// {
// 	cl_int				type;
// 	cl_float3			pos;
// 	cl_float3			dir;
// 	cl_int				shrink;
// 	cl_float			brightness;
// 	cl_int				color;
// }						t_light;

// typedef struct			s_plane
// {
// 	cl_float3			pos;
// 	cl_float3			normale;
// 	cl_int				color;
// 	cl_float3			diff;
// 	cl_float3			spec;
// 	cl_float			reflex;
// }						t_plane;

// typedef struct			s_sphere
// {
// 	cl_float3			pos;
// 	cl_float3			dir;
// 	cl_float			radius;
// 	cl_int				color;
// 	cl_float3			diff;
// 	cl_float3			spec;
// 	cl_float			reflex;
// }						t_sphere;

// typedef struct			s_param
// {
// 	int					n_cams;
// 	int					n_cones;
// 	int					n_cylinders;
// 	int					n_lights;
// 	int					n_planes;
// 	int					n_spheres;
// 	int					active_cam;
// 	int					win_w;
// 	int					win_h;
// 	cl_float3			mvt;
// 	cl_float3			ambient;
// 	int					mou_x;
// 	int					mou_y;
// 	int					depth;
// }						t_param;

// typedef struct			s_node
// {
// 	int					id;
// 	int					type;
// 	cl_float			fov;
// 	cl_float3			dir;
// 	cl_float3			pos;
// 	cl_float3			normale;
// 	cl_float			radius;
// 	cl_float			angle;
// 	cl_int				color;
// 	cl_int				light;
// 	cl_int				shrink;
// 	cl_float			brightness;
// 	cl_float			height;
// 	cl_float3			diff;
// 	cl_float3			spec;
// 	cl_float			reflex;
// 	struct s_node		*next;
// }						t_node;

// typedef	struct			s_xml
// {
// 	char				*scene;
// 	int					scene_fd;
// 	char				**nodes;
// 	char				**sub_node;
// 	t_node				*node_lst;
// 	char				is_comm;
// 	char				in_scene;
// 	int					n_nodes;
// 	int					n_sub;
// 	int					lbra;
// 	int					rbra;
// 	int					slas;
// 	int					dquo;
// 	int					excl;
// }						t_xml;

// typedef struct			s_frame
// {
// 	void				*ptr;
// 	char				*pix;
// 	int					x;
// 	int					y;
// 	int					w;
// 	int					h;
// 	int					row;
// 	int					bpp;
// 	int					endian;
// }						t_frame;

// typedef	struct			s_tor
// {
// 	cl_float3			prim;
// 	unsigned int		hit_type;
// 	unsigned int		hit_id;
// 	unsigned int		color;
// 	char				check_g;
// 	char				check_d;
// }						t_tor;

// typedef struct			s_scene
// {
// 	t_cam				*cameras;
// 	t_cone				*cones;
// 	t_cylinder			*cylinders;
// 	t_light				*lights;
// 	t_plane				*planes;
// 	t_sphere			*spheres;
// 	unsigned int		n_cams;
// 	unsigned int		n_cones;
// 	unsigned int		n_cylinders;
// 	unsigned int		n_lights;
// 	unsigned int		n_planes;
// 	unsigned int		n_spheres;
// 	unsigned int		active_cam;
// 	unsigned int		win_w;
// 	unsigned int		win_h;
// 	cl_float3			ambient;
// 	int					mou_x;
// 	int					mou_y;
// 	int					depth;
// 	float				u_time;
// 	int					flag;
// 	int					tor_count;
// }						t_scene;

// typedef	struct			s_env
// {
// 	void				*mlx;
// 	void				*win;
// 	t_frame				*frame;
// 	t_key				keys;
// 	int					win_w;
// 	int					win_h;
// 	int					sce_w;
// 	int					sce_h;
// 	int					cen_x;
// 	int					cen_y;
// 	int					debug;
// 	t_xml				*xml;
// 	char				*kernel_src;
// 	cl_int				err;
// 	cl_device_id		device_id;
// 	cl_context			context;
// 	cl_command_queue	raytrace_queue;
// 	cl_program			program;
// 	cl_kernel			kernel_rt;
// 	cl_mem				frame_buffer;
// 	cl_mem				target_obj_buf;
// 	t_hit				target_obj;
// 	int					gpu;
// 	size_t				global;
// 	size_t				local;
// 	unsigned int		count;

// 	t_cam				*cameras;
// 	cl_mem				cameras_mem;
// 	t_cone				*cones;
// 	cl_mem				cones_mem;
// 	t_cylinder			*cylinders;
// 	cl_mem				cylinders_mem;
// 	t_light				*lights;
// 	cl_mem				lights_mem;
// 	t_plane				*planes;
// 	cl_mem				planes_mem;
// 	t_sphere			*spheres;
// 	cl_mem				spheres_mem;

// 	t_scene				*scene;
// 	cl_mem				scene_mem;
// 	t_fps				fps;

// 	char				run;
// 	int					node_count;
// }						t_env;

#endif
