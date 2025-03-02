#version 330 core
out vec4 FragColor;
in vec3 Color; // Color for empty squares
in vec2 TexCoord; // Texture coordinates

uniform sampler2D texture1; // Texture sampler
uniform bool hasPiece; // Whether the square has a piece

void main()
{
    if (hasPiece) {
        // If the square has a piece, apply the texture
        FragColor = texture(texture1, TexCoord);
    } else {
        // If no piece, apply the color for the empty square
        FragColor = vec4(Color, 1.0f);  // Use the passed color for empty square
    }
}
