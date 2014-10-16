
attribute vec4 position;
uniform mat4 modelViewProjectionMatrix;
uniform sampler2D texture;

void main()
{
    gl_Position = modelViewProjectionMatrix * position;
}
