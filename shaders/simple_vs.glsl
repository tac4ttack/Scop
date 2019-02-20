#version 330 core
layout (location = 0) in vec4 aPos;
void main()
{
		gl_Position = vec4(aPos.x, aPos.y, aPos.z, aPos.w);
}



// #version 330 core
// layout(location = 0) in vec3 vertexPosition_modelspace;
// void main(){
//   gl_Position.xyz = vertexPosition_modelspace;
//   gl_Position.w = 1.0;
// }


// #version 420

// in vec3 vertex_position;

// void main() {
//   gl_Position = vec4(vertex_position, 1.0);
// }
