#version 330 core

// Output colors in RGBA
out vec4 FragColor;


// Import the color from the Vertex Shader
in vec3 color;
// Import the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Import the normal from the Vertex Shader
in vec3 Normal;
// Import the current position from the Vertex Shader
in vec3 crntPos;

// Get the Texture Unit from the main function
uniform sampler2D tex0;
// Get the light color from the main function
uniform vec4 lightColor;
// Get the light position from the main function
uniform vec3 lightPos;
// Get the camera position from the main function
uniform vec3 camPos;

void main()
{
	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	// output final color
	FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
}