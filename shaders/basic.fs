#version 330 core

in vec4 posPass;
in vec2 TexCoord;

out vec4 fragColor;

uniform sampler2D tex;
uniform int picked;

void main()
{
    fragColor = texture(tex, TexCoord);
    if (picked == 1)
        fragColor = vec4(1.0f, 0.0f, 0.0f, 0.0f);
}
