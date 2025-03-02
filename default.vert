#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord; // Texture coordinates

out vec3 Color;
out vec2 TexCoord; // Pass texture coordinates to fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0);
    Color = aColor;
    TexCoord = aTexCoord; // Pass the texture coordinates
}
