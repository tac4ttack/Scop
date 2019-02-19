/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_loader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 15:35:55 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/07 11:19:30 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int		shader_reader(int fd, char **target)
{
	int status;
	char *tmp;

	status = 1;
	if (fd > 0)
	{
		while (status == 1)
		{
			if ((status = get_next_line(fd, &tmp)) == -1)
				temp_error("[shader_reader] ERROR: Problem occured while reading shader file");
			else if (status == 0)
				break;
			else
				*target = ft_strjoin(*target, tmp);
		}
		close(fd);
		return (0);
	}
	else
		return (-1);

}

GLuint shader_loader(const char **files, int length)
{
	int fd;
	int i;
	char **shaders_source_code;
	// GLint Result = GL_FALSE;
	// int InfoLogLength;
	// char *VertexShaderErrorMessage;
	// char * FragmentShaderErrorMessage;
	// char *ProgramErrorMessage;

	if (!(shaders_source_code = (char**)malloc((size_t)length)))
		temp_error("[shader_loader] ERROR: Couldn't allocate memory for storing shaders source code");
	i = length - 1;
	if (files)
	{
		// Read and store shaders source code
		while (i >= 0)
		{
			if ((fd = open(files[i], O_RDONLY)) < 0)
				temp_error("[shader_loader] ERROR: Couldn't load shader file");
			else
			{
				shaders_source_code[i] = ft_strdup(files[i]);
				ft_bzero((void*)shaders_source_code[i], ft_strlen(shaders_source_code[i]));
				if (shader_reader(fd, &shaders_source_code[i]) == -1)
					temp_error("[shader_loader] ERROR: Couldn't read shader file");
			}
			i--;
		}

		// Create the shaders, first the VertexShader
		// GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		// glShaderSource(VertexShaderID, 1, (const GLchar *const *)shaders_source_code[0], NULL);
		// glCompileShader(VertexShaderID);
		// Check Vertex Shader
		// glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		// glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		// if (InfoLogLength > 0 )
		// {
		// 	VertexShaderErrorMessage = ft_strnew((size_t)InfoLogLength + 1);
		// 	glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, VertexShaderErrorMessage);
		// 	printf("Vertex Shader loading error:\n%s\n", VertexShaderErrorMessage);
		// }

		// then the Fragment Shader
		// GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		// glShaderSource(FragmentShaderID, 1, (const GLchar *const *)shaders_source_code[1], NULL);
		// glCompileShader(FragmentShaderID);
		// Check Fragment Shader
		// glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		// glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		// if ( InfoLogLength > 0 ){
		// 	FragmentShaderErrorMessage = ft_strnew((size_t)InfoLogLength + 1);
		// 	glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, FragmentShaderErrorMessage);
		// 	printf("Fragment Shader loading error:\n%s\n", FragmentShaderErrorMessage);
		// }

		// Create the ProgramID
		// GLuint ProgramID = glCreateProgram();
		// Attach Shaders to the program
		// glAttachShader(ProgramID, VertexShaderID);
		// glAttachShader(ProgramID, FragmentShaderID);
		// Link the program
		// glLinkProgram(ProgramID);
		// Check the program
		// glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
		// glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		// if ( InfoLogLength > 0 ){
		// 	ProgramErrorMessage = ft_strnew((size_t)InfoLogLength + 1);
		// 	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, ProgramErrorMessage);
		// 	printf("Error creating the Shader Program:\n%s\n", ProgramErrorMessage);
		// }

		// glGetUniformLocation(ProgramID );

		// Cleaning
		// glDetachShader(ProgramID, VertexShaderID);
		// // glDetachShader(ProgramID, FragmentShaderID);
		// glDeleteShader(VertexShaderID);
		// glDeleteShader(FragmentShaderID);

		return 0;
		// return ProgramID;
	}
	else
		return -1;
}