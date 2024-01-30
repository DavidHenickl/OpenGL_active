#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;
// Normals (not necessarily normalized)
layout (location = 3) in vec3 aNormal;


// Output the color for the Fragment Shader
out vec3 color;
// Output the texture coordinates to the Fragment Shader
out vec2 texCoord;
// Output the normal for the Fragment Shader
out vec3 Normal;
// Output the current position for the Fragment Shader
out vec3 crntPos;

// Import the camera matrix from the main function
uniform mat4 camMatrix;
// Import the model matrix from the main function
uniform mat4 model;


void main()
{
	// calculate current position
	crntPos = vec3(model * vec4(aPos, 1.0f));
	// Output the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(crntPos, 1.0);

	// Assign the colors from the Vertex Data to "color"
	color = aColor;
	// Assign the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;
	// Assign the normal from the Vertex Data to "Normal"
	Normal = aNormal;
}