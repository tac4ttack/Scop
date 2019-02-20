#include "scop.h"


void _update_fps_counter(GLFWwindow *window)
{
	static double previous_seconds;
	previous_seconds = glfwGetTime();
	static int frame_count;
	double current_seconds = glfwGetTime();
	double elapsed_seconds = current_seconds - previous_seconds;
	// fprintf(stdout, "prev = %f\ncur = %f\nelapse = %f\n", previous_seconds, current_seconds, elapsed_seconds);
	// if (elapsed_seconds > 0.25) // threshold too small? 0.00001
	if (elapsed_seconds > 0.25)
	{
		previous_seconds = current_seconds;
		double fps = (double)frame_count / elapsed_seconds;
		char tmp[128];
		sprintf(tmp, "opengl @ fps: %.2f", fps);
		glfwSetWindowTitle(window, tmp);
		frame_count = 0;
	}
	frame_count++;
}

int main()
{

	// // start GL context and O/S window using the GLFW helper library
	// if (!glfwInit())
	// {
	// 	fprintf(stderr, "ERROR: could not start GLFW3\n");
	// 	return 1;
	// }



	// GLFWwindow *window;
	// if (!(window = glfwCreateWindow(1024, 768, "Scop - testing", NULL, NULL)))
	// {
	// 	gl_log_err("ERROR: could not open window with GLFW3\n");
	// 	glfwTerminate();
	// 	return 1;
	// }
	// // Attach window and context
	// glfwMakeContextCurrent(window);

	// // Set up a callback for windows resize
	// glfwSetWindowSizeCallback(window, window_size_callback);

	// Glew
	// To improve support for newer OpenGL releases
	// glewExperimental = GL_TRUE;
	// // start GLEW extension handler
	// if (glewInit() != GLEW_OK)
	// {
	// 	gl_log_err("Failed to initialize GLEW\n");
	// 	return -1;
	// }

	// // Print opengl params into the gl.log
	// gl_log_params();

	// // get version info
	// const GLubyte *renderer = glGetString(GL_RENDERER); // get renderer string
	// const GLubyte *version = glGetString(GL_VERSION);   // version as a string
	// gl_log("Renderer: %s\n", renderer);
	// gl_log("OpenGL version supported %s\n", version);

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	// these two are messing up with the drawing order it seems


	// defining some points
	// Here we define our triangle, vertex are read in clockwise order
	float points_A[] =
	{
		// 0.0f, 0.5f, 0.0f,
		// 0.5f, -0.5f, 0.0f,
		// -0.5f, -0.5f, 0.0f
		-10.0f,  10.0f, -10.0f,
		-10.0f, -10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,
		10.0f,  10.0f, -10.0f,
		-10.0f,  10.0f, -10.0f,

		-10.0f, -10.0f,  10.0f,
		-10.0f, -10.0f, -10.0f,
		-10.0f,  10.0f, -10.0f,
		-10.0f,  10.0f, -10.0f,
		-10.0f,  10.0f,  10.0f,
		-10.0f, -10.0f,  10.0f,

		10.0f, -10.0f, -10.0f,
		10.0f, -10.0f,  10.0f,
		10.0f,  10.0f,  10.0f,
		10.0f,  10.0f,  10.0f,
		10.0f,  10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,

		-10.0f, -10.0f,  10.0f,
		-10.0f,  10.0f,  10.0f,
		10.0f,  10.0f,  10.0f,
		10.0f,  10.0f,  10.0f,
		10.0f, -10.0f,  10.0f,
		-10.0f, -10.0f,  10.0f,

		-10.0f,  10.0f, -10.0f,
		10.0f,  10.0f, -10.0f,
		10.0f,  10.0f,  10.0f,
		10.0f,  10.0f,  10.0f,
		-10.0f,  10.0f,  10.0f,
		-10.0f,  10.0f, -10.0f,

		-10.0f, -10.0f, -10.0f,
		-10.0f, -10.0f,  10.0f,
		10.0f, -10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,
		-10.0f, -10.0f,  10.0f,
		10.0f, -10.0f,  10.0f
	};

	// We need to store these vertex into a buffer, a Vertex Buffer Object (VBO)
	GLuint vertex_buffer_object_A = 0;
	glGenBuffers(1, &vertex_buffer_object_A);									// empty buffer generation
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_A);						// set buffer as current buffer in OpenGL's state machine
	glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), points_A, GL_STATIC_DRAW); // copy the points into buffer, tells GL that the buffer is the size of 9 floating point numbers, and gives it the address of the first value.

	// The Vertex Array Object (VAO) will store all the VBOs we want to use
	GLuint vertex_array_object_A = 0;
	glGenVertexArrays(1, &vertex_array_object_A); // empty vao generation
	glBindVertexArray(vertex_array_object_A);	 // set vao as current
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); // "0" means define the layout for attribute number 0. "3" means that the variables are vec3 made from every 3 floats (GL_FLOAT) in the buffer.

	float points_B[] =
	{
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,

		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	// We need to store these vertex into a buffer, a Vertex Buffer Object (VBO)
	GLuint vertex_buffer_object_B = 0;
	glGenBuffers(1, &vertex_buffer_object_B);									 // empty buffer generation
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_B);						 // set buffer as current buffer in OpenGL's state machine
	glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(float), points_B, GL_STATIC_DRAW); // copy the points into buffer, tells GL that the buffer is the size of 9 floating point numbers, and gives it the address of the first value.

	// The Vertex Array Object (VAO) will store all the VBOs we want to use
	GLuint vertex_array_object_B = 0;
	glGenVertexArrays(1, &vertex_array_object_B); // empty vao generation
	glBindVertexArray(vertex_array_object_B);	 // set vao as current
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); // "0" means define the layout for attribute number 0. "3" means that the variables are vec3 made from every 3 floats (GL_FLOAT) in the buffer.

	// shader part //
	// vertex shader describe where are positionned the vertexes
	const char *vertex_shader =
		"#version 400\n"
		"in vec3 vp;"
		"void main() {"
		"  gl_Position = vec4(vp.x, vp.y, vp.z, 42.0);"
		"}";
	// vertex shader creation
	GLuint vs = glCreateShader(GL_VERTEX_SHADER); // gen empty vs
	glShaderSource(vs, 1, &vertex_shader, NULL);  // load the sources
	glCompileShader(vs);						  // compile the sources

	// fragment shader describe how to colorize the shape
	const char *fragment_shader =
		"#version 400\n"
		"uniform vec4 inputColor;"
		"out vec4 frag_colour;"
		"void main() {"
		"frag_colour = vec4(0.1, 0.21, 0.32, 1.0);"
		// "frag_colour = inputColor;"
		"}";
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	// creating a shader program because we need to combine the 2 previous shader into a gpu executable shader program
	GLuint shader_programme = glCreateProgram(); // gen empty shader program
	glAttachShader(shader_programme, fs);		 // attach the fragment shader
	glAttachShader(shader_programme, vs);		 // attach the vertex shader
	glLinkProgram(shader_programme);			 // link them together

	// vertex shader describe where are positionned the vertexes
	const char *vertex_shader_2 =
		"#version 400\n"
		"in vec3 vp;"
		"void main() {"
		"  gl_Position = vec4(vp.x, vp.y, vp.z, 1.0);"
		"}";
	// vertex shader creation
	GLuint vs_2 = glCreateShader(GL_VERTEX_SHADER);  // gen empty vs
	glShaderSource(vs_2, 1, &vertex_shader_2, NULL); // load the sources
	glCompileShader(vs_2);							 // compile the sources

	const char *fragment_shader_2 =
		"#version 400\n"
		"uniform float time;"
		"out vec4 frag_colour;"
		"void main() {"
		"  frag_colour = vec4(0.42, 0.2, 0.76, 1.0);"
		"}";

	GLuint fs_2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs_2, 1, &fragment_shader_2, NULL);
	glCompileShader(fs_2);
	// creating a shader program because we need to combine the 2 previous shader into a gpu executable shader program
	GLuint shader_program_2 = glCreateProgram(); // gen empty shader program
	glAttachShader(shader_program_2, fs_2);		 // attach the fragment shader
	glAttachShader(shader_program_2, vs_2);		 // attach the vertex shader
	glLinkProgram(shader_program_2);			 // link them together

	// set up color used to fill with a glClear
	glClearColor(0.21, 0.21, 0.21, 0.0);

	// drawing //
	while (!glfwWindowShouldClose(window))
	{
		_update_fps_counter(window);

		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shader_programme);			  // specify which shader program to use
		glBindVertexArray(vertex_array_object_A); // specify which VBO to use
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays(GL_LINE_LOOP, 0, 36);

		glUseProgram(shader_program_2);			  // specify which shader program to use
		glBindVertexArray(vertex_array_object_B); // specify which VBO to use
		glDrawArrays(GL_LINE_LOOP, 0, 6);

		// update other events like input handling
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);

		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window, 1);
	}

	// Cleaning
	glDetachShader(shader_programme, vs);
	glDetachShader(shader_programme, fs);
	glDeleteShader(vs);
	glDeleteShader(fs);

	// close GL context and any other GLFW resources
	glfwTerminate();

	return 0;
}
