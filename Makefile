# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/01 16:47:13 by fmessina          #+#    #+#              #
#    Updated: 2019/02/26 14:36:20 by fmessina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = 					scop
CURRENT_PATH :=			$(shell pwd)
CC = 					clang
CFLAGS +=				-Wall -Wextra -Werror
OFLAGS := 				-O3

SCOP_INCLUDE =			-I $(SCOP_INCLUDES_PATH)
SCOP_INCLUDES_PATH =	./includes
SCOP_INCLUDES =			$(addprefix $(SCOP_INCLUDES_PATH)/,$(SCOP_INCLUDES_FILES))
SCOP_INCLUDES_FILES =	scop.h

LIBFT_PATH :=			./lib/libft
LIBFT_INCLUDE :=		-I $(LIBFT_PATH)
LIBFT_LINK :=			-L $(LIBFT_PATH) -lft

LIBMATH_LINK :=			-lm

GLEW_PATH :=			./lib/glew-2.1.0
GLEW_INCLUDE =			-I $(GLEW_PATH)/include
GLEW_LINK =				-L $(GLEW_PATH)/lib $(GLEW_LIB_FILE)
GLEW_LIB_FILE =			$(shell ls $(GLEW_PATH)/lib/libGLEW.a)

GLFW_PATH :=			./lib/glfw-3.2.1
GLFW_BUILD_PATH := 		$(GLFW_PATH)/glfw-build
GLFW_INCLUDE =			-I $(GLFW_PATH)/include
GLFW_LINK =				-L $(GLFW_BUILD_PATH)/src $(GLFW_LIB_FILE)
GLFW_LIB_FILE =			$(shell ls $(GLFW_BUILD_PATH)/src/libglfw3.a)

FRAMEWORKS =			-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

OBJ =					$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
OBJ_PATH =				./obj
OBJ_NAME =				$(SRC_FILES:.c=.o)

SRC =					$(addprefix $(SRC_PATH)/,$(SRC_FILES))
SRC_PATH =				./src
SRC_FILES =  			buffer/buffer_create.c \
						log/scop_log_gl_params.c \
						log/scop_log_restart.c \
						log/scop_log.c \
						glfw/glfw_error_callback.c \
						glfw/glfw_launch.c \
						glfw/glfw_window_size_callback.c \
						init.c \
						main.c \
						mesh/mesh_clean.c \
						mesh/mesh_file_load.c \
						mesh/mesh_file_process.c \
						mesh/mesh_get_face_type.c \
						mesh/mesh_line_check.c \
						mesh/mesh_line_process.c \
						mesh/mesh_line_process_face.c \
						mesh/mesh_line_process_normal.c \
						mesh/mesh_line_process_texture.c \
						mesh/mesh_line_process_vertex.c \
						mesh/mesh_print_data.c \
						mesh/mesh_print_data_face.c \
						mesh/mesh_print_data_normal.c \
						mesh/mesh_print_data_texture.c \
						mesh/mesh_print_data_vertex.c \
						mesh/mesh_process_face.c \
						shader/shader_build.c \
						shader/shader_uniform.c \
						utility/split_destroy.c \
						utility/error.c \
						utility/exit.c \
						utility/flush.c

OS_TEST := $(shell uname)
ifeq ($(OS_TEST), Darwin)
MACOSX = -DMACOSX
endif

default: all

all: libft glew glfw $(NAME)

$(NAME): $(SRC) $(SCOP_INCLUDES) $(OBJ_PATH) $(OBJ)
	@echo "\n$(GREEN)Compiling $(NAME) for MacOSX $(OS_NAME)$(EOC)"
	$(CC) -o $@ $(OBJ) $(LIBFT_LINK) $(LIBMATH_LINK) $(GLEW_LINK) $(GLFW_LINK) $(FRAMEWORKS) $(ASANFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@ $(SCOP_INCLUDE) $(LIBFT_INCLUDE) $(GLEW_INCLUDE) $(GLFW_INCLUDE) $(DEBUG_MACRO) $(ASANFLAGS) $(MACOSX)

$(OBJ_PATH):
	@echo "$(GREEN)Creating ./obj path and making binaries from source files$(EOC)"
	@mkdir $(OBJ_PATH)
	@mkdir $(OBJ_PATH)/buffer
	@mkdir $(OBJ_PATH)/log
	@mkdir $(OBJ_PATH)/glfw
	@mkdir $(OBJ_PATH)/mesh
	@mkdir $(OBJ_PATH)/shader
	@mkdir $(OBJ_PATH)/utility

clean:
	@echo "$(GREEN)Cleaning...$(EOC)"
	@echo "$(GREEN)Deleting .obj files$(EOC)"
	@rm -rf $(OBJ_PATH)

fclean: clean
	@echo "$(GREEN)Full cleaning...$(EOC)"
	@echo "$(GREEN)Deleting $(NAME) executable and config file$(EOC)"
	@rm -rf $(NAME) ./config.json

fcleanmega: fcleanlibft fclean glewclean glfwclean

libft:
	@echo $(SCOP_INCLUDES)

	@echo "$(GREEN)Compiling$(EOC) $(YELL)Libft$(EOC) $(GREEN)library$(EOC)"
	@make -C $(LIBFT_PATH)/ all

cleanlibft:
	@echo "$(GREEN)Cleaning$(EOC) $(YELL)Libft$(EOC) $(GREEN)library's folders$(EOC)"
	@make -C $(LIBFT_PATH)/ clean

fcleanlibft: cleanlibft
	@echo "$(GREEN)Cleaning$(EOC) $(YELL)Libft$(EOC) $(GREEN)library's folders and deleting binary$(EOC)"
	@make -C $(LIBFT_PATH)/ fclean

glew:
	@echo "\n$(GREEN)Compiling$(EOC) $(YELL)GLEW$(EOC) $(GREEN)library$(EOC)"
ifeq ($(GLEW_LIB_FILE), $(GLEW_PATH)/lib/libGLEW.a)
	@echo "$(YELL)GLEW$(EOC) $(GREEN)library already present and compiled, skipping step...$(EOC)"
else
	@make -C $(GLEW_PATH)
endif

glewclean:
	@echo "$(GREEN)Cleaning$(EOC) $(YELL)GLEW$(EOC) $(GREEN)library$(EOC)"
	@make -C $(GLEW_PATH)/ clean

glfw:
	@echo "\n$(GREEN)Compiling$(EOC) $(YELL)GLFW$(EOC) $(GREEN)library$(EOC)"
ifeq ($(GLFW_LIB_FILE), $(GLFW_BUILD_PATH)/src/libglfw3.a)
	@echo "$(YELL)GLFW$(EOC) $(GREEN)library already present and compiled, skipping step...$(EOC)"
else
	@echo "$(GREEN)Cleaning$(EOC) $(YELL)GLFW$(EOC) $(GREEN)library path$(EOC)"
	@rm -rf $(GLFW_BUILD_PATH)
	@mkdir $(GLFW_BUILD_PATH)
	@echo "$(GREEN)Generating$(EOC) $(YELL)GLFW$(EOC) $(GREEN)library's makefile$(EOC)"
	@cmake -S $(GLFW_PATH) -B $(GLFW_BUILD_PATH)
	@echo "$(GREEN)Building$(EOC) $(YELL)GLFW$(EOC) $(GREEN)library$(EOC)"
	@make -C $(GLFW_BUILD_PATH)
endif

glfwclean:
	@echo "$(GREEN)Cleaning$(EOC) $(YELL)GLFW$(EOC) $(GREEN)library's files$(EOC)"
	@rm -rf $(GLFW_BUILD_PATH)

re: fclean default

debug: clean cleanlibft debuglibft debug_flag all
debug_asan: clean cleanlibft debug_asan_flag debug
debug_flag:
	$(eval DEBUG_MACRO = -DDEBUG -g)
debug_asan_flag:
	$(eval ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer)

debuglibft:
	@echo "$(GREEN)Compiling$(EOC) $(YELL)Libft$(EOC) $(GREEN)library with ASan$(EOC)"
	make -C $(LIBFT_PATH)/ debug all

# brewinstall:
# 	@echo "$(GREEN)Updating$(EOC) $(YELL)Brew$(EOC) $(GREEN)package$(EOC)"
# 	@brew update
# 	@echo "$(GREEN)Installing$(EOC) $(YELL)readline$(EOC) $(GREEN)package$(EOC)"
# 	@brew install -f readline
# 	@echo "$(GREEN)Installing$(EOC) $(YELL)sqlite$(EOC) $(GREEN)package$(EOC)"
# 	@brew install -f sqlite
# 	@echo "$(GREEN)Installing$(EOC) $(YELL)xz$(EOC) $(GREEN)package$(EOC)"
# 	@brew install -f xz
# 	@echo "$(GREEN)Installing$(EOC) $(YELL)openssl$(EOC) $(GREEN)package$(EOC)"
# 	@brew install -f openssl
# 	@echo "$(GREEN)Installing$(EOC) $(YELL)gdbm$(EOC) $(GREEN)package$(EOC)"
# 	@brew install -f gdbm
# 	@echo "$(GREEN)Installing$(EOC) $(YELL)python$(EOC) $(GREEN)package$(EOC)"
# 	@brew install -f python
# 	@echo "$(GREEN)Installing$(EOC) $(YELL)sphinx-doc$(EOC) $(GREEN)package$(EOC)"
# 	@brew install -f sphinx-doc
# 	@echo "$(GREEN)Installing$(EOC) $(YELL)cmake$(EOC) $(GREEN)package$(EOC)"
# 	@brew install -f cmake
# 	@echo "$(GREEN)Installing$(EOC) $(YELL)pkg-config$(EOC) $(GREEN)package$(EOC)"
# 	@brew install -f pkg-config

# brewuninstall:
# 	# @echo "$(GREEN)Uninstalling$(EOC) $(YELL)pkg-config$(EOC) $(GREEN)package$(EOC)"
# 	# @brew uninstall -f pkg-config
# 	@echo "$(GREEN)Uninstalling$(EOC) $(YELL)cmake$(EOC) $(GREEN)package$(EOC)"
# 	@brew uninstall -f cmake
# 	@echo "$(GREEN)Uninstalling$(EOC) $(YELL)sphinx-doc$(EOC) $(GREEN)package$(EOC)"
# 	@brew uninstall -f sphinx-doc
# 	@echo "$(GREEN)Uninstalling$(EOC) $(YELL)python$(EOC) $(GREEN)package$(EOC)"
# 	@brew uninstall -f python
# 	@echo "$(GREEN)Uninstalling$(EOC) $(YELL)gdbm$(EOC) $(GREEN)package$(EOC)"
# 	@brew uninstall -f gdbm
# 	@echo "$(GREEN)Uninstalling$(EOC) $(YELL)openssl$(EOC) $(GREEN)package$(EOC)"
# 	@brew uninstall -f openssl
# 	@echo "$(GREEN)Uninstalling$(EOC) $(YELL)xz$(EOC) $(GREEN)package$(EOC)"
# 	@brew uninstall -f xz
# 	@echo "$(GREEN)Uninstalling$(EOC) $(YELL)sqlite$(EOC) $(GREEN)package$(EOC)"
# 	@brew uninstall -f sqlite
# 	@echo "$(GREEN)Uninstalling$(EOC) $(YELL)readline$(EOC) $(GREEN)package$(EOC)"
# 	@brew uninstall -f readline

norme:
	norminette $(SRC_PATH)
	norminette $(SCOP_INCLUDES_PATH)
	norminette $(LIBFT_PATH)

# usage:
# 	@echo "\n$(B_RED)Please use one of the following commands:$(EOC)\n"
# 	@echo "\tCompile and compute with one $(GREEN)CPU$(EOC) thread -> $(B_YELL)make cpu$(EOC)\n"
# 	@echo "\tCompile the $(GREEN)LIBFT$(EOC) -> $(B_YELL)make libft$(EOC)\n"
# 	@echo "\tCompile the $(GREEN)MLX$(EOC) (according to your OS) -> $(B_YELL)make mlx$(EOC)\n"
# 	@echo "\tCheck the $(GREEN)42 C STANDARD$(EOC) in sources and includes directories -> $(B_YELL)make norme$(EOC)\n"
# 	@echo "\tClean the $(GREEN)$(NAME)$(EOC) directory from object files -> $(B_YELL)make clean$(EOC)\n"
# 	@echo "\tClean the $(GREEN)LIBFT$(EOC) directory from object files -> $(B_YELL)make cleanlibft$(EOC)\n"
# 	@echo "\tClean the $(GREEN)MLX$(EOC) directory from object files -> $(B_YELL)make cleanmlx$(EOC)\n"
# 	@echo "\tRemove object files and binaries from $(GREEN)$(NAME) LIBFT and MLX$(EOC) directories -> $(B_YELL)make fclean$(EOC)\n"
# 	@echo "\tRemove object files and binaries from $(GREEN)LIBFT$(EOC) directory -> $(B_YELL)make fcleanlibft$(EOC)\n"
# 	@echo "\tRemove object files and binaries from $(GREEN)$(NAME)$(EOC) directory then compile it again using one $(GREEN)CPU$(EOC) thread -> $(B_YELL)make re$(EOC)\n"
# 	@echo "\t$(B_RED)NOT IMPLEMENTED YET!$(EOC) Compile and compute with $(GREEN)OpenCL$(EOC) using multiple threads -> $(B_YELL)make gpu$(EOC)\n"
# 	@echo "\tIf you want to activate the debugging output add \
# 	$(GREEN)debug$(EOC) before -> $(B_YELL)make debug cpu$(EOC)\n"


######
## REDO YOUR FUCKIN' PHONY!!!!!!
##
.PHONY: all clean fclean re libft cleanlibft fcleanlibft debug usage norme
#####

## SHELL COLOR CODES ##
GREY =					\x1b[2;29m
BLACK =					\x1b[2;30m
RED =					\x1b[2;31m
GREEN =					\x1b[2;32m
YELL =					\x1b[2;33m
BLUE =					\x1b[2;34m
PINK =					\x1b[2;35m
CYAN =					\x1b[2;36m
WHIT =					\x1b[2;37m
WHIBLK =				\x1b[2;40m
WHIRED =				\x1b[2;41m
WHIGRE =				\x1b[2;42m
WHIYEL =				\x1b[2;43m
WHIBLU =				\x1b[2;44m
WHIPI =					\x1b[2;45m
WHICYA =				\x1b[2;46m
B_GREY =				\x1b[1;29m
B_BLACK =				\x1b[1;30m
B_RED =					\x1b[1;31m
B_GREEN =				\x1b[1;32m
B_YELL =				\x1b[1;33m
B_BLUE =				\x1b[1;34m
B_PINK =				\x1b[1;35m
B_CYAN =				\x1b[1;36m
B_WHIT =				\x1b[1;37m
B_WHIBLK =				\x1b[1;40m
B_WHIRED =				\x1b[1;41m
B_WHIGRE =				\x1b[1;42m
B_WHIYEL =				\x1b[1;43m
B_WHIBLU =				\x1b[1;44m
B_WHIPI =				\x1b[1;45m
B_WHICYA =				\x1b[1;46m
U_GREY =				\x1b[4;29m
U_BLACK =				\x1b[4;30m
U_RED =					\x1b[4;31m
U_GREEN =				\x1b[4;32m
U_YELL =				\x1b[4;33m
U_BLUE =				\x1b[4;34m
U_PINK =				\x1b[4;35m
U_CYAN =				\x1b[4;36m
U_WHIT =				\x1b[4;37m
U_WHIBLK =				\x1b[4;40m
U_WHIRED =				\x1b[4;41m
U_WHIGRE =				\x1b[4;42m
U_WHIYEL =				\x1b[4;43m
U_WHIBLU =				\x1b[4;44m
U_WHIPI =				\x1b[4;45m
U_WHICYA =				\x1b[4;46m
IC_GREY =				\x1b[2;29m
IC_BLACK =				\x1b[2;30m
IC_RED =				\x1b[2;31m
IC_GREEN =				\x1b[2;32m
IC_YELL =				\x1b[2;33m
IC_BLUE =				\x1b[2;34m
IC_PINK =				\x1b[2;35m
IC_CYAN =				\x1b[2;36m
IC_WHIT =				\x1b[2;37m
IC_WHIBLK =				\x1b[2;40m
IC_WHIRED =				\x1b[2;41m
IC_WHIGRE =				\x1b[2;42m
IC_WHIYEL =				\x1b[2;43m
IC_WHIBLU =				\x1b[2;44m
IC_WHIPI =				\x1b[2;45m
IC_WHICYA =				\x1b[7;46m
EOC =					\x1b[0m
