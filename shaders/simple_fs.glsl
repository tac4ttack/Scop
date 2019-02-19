// #version 430 core
// out vec3 color;
// void main(){
//   color = vec3(1,0,0);
// }

#version 420

uniform vec4 inputColour;
out vec4 fragColour;

void main() {
  fragColour = inputColour;
}
